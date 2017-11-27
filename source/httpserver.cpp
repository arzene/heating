#include <httpserver.h>

/*
 * system include
 * */ 
#include <string.h>
#include <sys/stat.h>	// struct stat
#include <stdlib.h>	//	malloc()
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>	// close()

/*
 * system libraries
 * */
#include <event.h>
#include <event2/http.h>

/*
 * project include
 * */
#include <HttpGetResponse.h>

using namespace std;
/* Callback used for the /dump URI, and for every non-GET request:
 * dumps all information to stdout and gives back a trivial 200 ok */
void environmentRequestHandler(struct evhttp_request *request, void *arg)
{
	
	const char *cmdtype;
	struct evkeyvalq *headers;
	struct evkeyval *header;
	struct evbuffer *buf;

	switch (evhttp_request_get_command(request))
	{
		case EVHTTP_REQ_GET: cmdtype = "GET"; break;
		case EVHTTP_REQ_POST: cmdtype = "POST"; break;
		case EVHTTP_REQ_HEAD: cmdtype = "HEAD"; break;
		case EVHTTP_REQ_PUT: cmdtype = "PUT"; break;
		case EVHTTP_REQ_DELETE: cmdtype = "DELETE"; break;
		case EVHTTP_REQ_OPTIONS: cmdtype = "OPTIONS"; break;
		case EVHTTP_REQ_TRACE: cmdtype = "TRACE"; break;
		case EVHTTP_REQ_CONNECT: cmdtype = "CONNECT"; break;
		case EVHTTP_REQ_PATCH: cmdtype = "PATCH"; break;
		default: cmdtype = "unknown"; break;
	}

	const char* uri = evhttp_request_get_uri(request);
	
	printf("Received a %s request for %s\nHeaders:\n", cmdtype, uri);
/*
 * headers
 * */
	headers = evhttp_request_get_input_headers(request);

	for (header = headers->tqh_first; header; header = header->next.tqe_next)
	{
		printf("  %s: %s\n", header->key, header->value);
	}
/*
 * input data
 * */
 
	buf = evhttp_request_get_input_buffer(request);
	puts("Input data: <<<");
	while (evbuffer_get_length(buf))
		{
		int n;
		char cbuf[128];
		n = evbuffer_remove(buf, cbuf, sizeof(cbuf));
		if (n > 0)
			(void) fwrite(cbuf, 1, n, stdout);
	}
	puts(">>>");

/*
 * decode query string 
 * */
	struct evhttp_uri* decoded = evhttp_uri_parse(uri);
	if (!decoded)
		{
		printf("It's not a good URI. Sending BADREQUEST\n");
		evhttp_send_error(request, HTTP_BADREQUEST, 0);
		return;
	}

	const char *query = evhttp_uri_get_query(decoded);
	/* Let's see what path the user asked for. */
	const char* path = evhttp_uri_get_path(decoded);

	/* We need to decode it, to see what path the user really wanted. */
	char *decoded_path = evhttp_uridecode(path, 0, NULL);

/*
 * GET response
 * */
	struct evbuffer *responseBuffer = evbuffer_new();

// add appropriate headers
//   evhttp_add_header(evhttp_request_get_input_headers(request), "Content-Type", "application/json");
//   evhttp_add_header(evhttp_request_get_input_headers(request), "Content-Length", responseHeader);

	JsonTemperatureResponse* jsonTemperatureResponse = (JsonTemperatureResponse*)arg;
	string jsonResultString = jsonTemperatureResponse->Get();
	evbuffer_add(responseBuffer, jsonResultString.c_str(), jsonResultString.size());

	evhttp_send_reply(request, 200, "OK", responseBuffer); 

	evbuffer_free(responseBuffer);
}

/* This callback gets invoked when we get any http request that doesn't match
 * any other callback.  Like any evhttp server callback, it has a simple job:
 * it must eventually call evhttp_send_error() or evhttp_send_reply().
 */
//static void send_document_cb(struct evhttp_request *req, void *arg)
//{
//	struct evbuffer *evb = NULL;
//	const char *docroot = (const char *)arg;
//	const char *uri = evhttp_request_get_uri(req);
//	struct evhttp_uri *decoded = NULL;
//	const char *path;
//	char *decoded_path;
//	char *whole_path = NULL;
//	size_t len;
//	int fd = -1;
//	struct stat st;
//
//	if (evhttp_request_get_command(req) != EVHTTP_REQ_GET) {
//		dump_request_cb(req, arg);
//		return;
//	}
//
//	printf("Got a GET request for <%s>\n",  uri);
//
//	/* Decode the URI */
//	decoded = evhttp_uri_parse(uri);
//	if (!decoded) {
//		printf("It's not a good URI. Sending BADREQUEST\n");
//		evhttp_send_error(req, HTTP_BADREQUEST, 0);
//		return;
//	}
//
//	/* Let's see what path the user asked for. */
//	path = evhttp_uri_get_path(decoded);
//	if (!path) path = "/";
//
//	/* We need to decode it, to see what path the user really wanted. */
//	decoded_path = evhttp_uridecode(path, 0, NULL);
//	if (decoded_path == NULL)
//		goto err;
//	/* Don't allow any ".."s in the path, to avoid exposing stuff outside
//	 * of the docroot.  This test is both overzealous and underzealous:
//	 * it forbids aceptable paths like "/this/one..here", but it doesn't
//	 * do anything to prevent symlink following." */
//	if (strstr(decoded_path, ".."))
//		goto err;
//
//	len = strlen(decoded_path)+strlen(docroot)+2;
//	if (!(whole_path = (char*)malloc(len))) {
//		perror("malloc");
//		goto err;
//	}
//	evutil_snprintf(whole_path, len, "%s/%s", docroot, decoded_path);
//
//	if (stat(whole_path, &st)<0) {
//		goto err;
//	}
//
//	/* This holds the content we're sending. */
//	evb = evbuffer_new();
//
//	if (S_ISDIR(st.st_mode)) {
//		/* If it's a directory, read the comments and make a little
//		 * index page */
//		DIR *d;
//		struct dirent *ent;
//
//		const char *trailing_slash = "";
//
//		if (!strlen(path) || path[strlen(path)-1] != '/')
//			trailing_slash = "/";
//
//		if (!(d = opendir(whole_path)))
//			goto err;
//
//		evbuffer_add_printf(evb,
//                    "<!DOCTYPE html>\n"
//                    "<html>\n <head>\n"
//                    "  <meta charset='utf-8'>\n"
//		    "  <title>%s</title>\n"
//		    "  <base href='%s%s'>\n"
//		    " </head>\n"
//		    " <body>\n"
//		    "  <h1>%s</h1>\n"
//		    "  <ul>\n",
//		    decoded_path, /* XXX html-escape this. */
//		    path, /* XXX html-escape this? */
//		    trailing_slash,
//		    decoded_path /* XXX html-escape this */);
//		while ((ent = readdir(d))) {
//			const char *name = ent->d_name;
//			evbuffer_add_printf(evb,
//			    "    <li><a href=\"%s\">%s</a>\n",
//			    name, name);/* XXX escape this */
//		}
//		evbuffer_add_printf(evb, "</ul></body></html>\n");
//		closedir(d);
//		evhttp_add_header(evhttp_request_get_output_headers(req),
//		    "Content-Type", "text/html");
//	} else {
//		/* Otherwise it's a file; add it to the buffer to get
//		 * sent via sendfile */
//		const char *type = guess_content_type(decoded_path);
//		if ((fd = open(whole_path, O_RDONLY)) < 0) {
//			perror("open");
//			goto err;
//		}
//
//		if (fstat(fd, &st)<0) {
//			/* Make sure the length still matches, now that we
//			 * opened the file :/ */
//			perror("fstat");
//			goto err;
//		}
//		evhttp_add_header(evhttp_request_get_output_headers(req),
//		    "Content-Type", type);
//		evbuffer_add_file(evb, fd, 0, st.st_size);
//	}
//
//	evhttp_send_reply(req, 200, "OK", evb);
//	goto done;
//err:
//	evhttp_send_error(req, 404, "Document was not found");
//	if (fd>=0)
//		close(fd);
//done:
//	if (decoded)
//		evhttp_uri_free(decoded);
//	if (decoded_path)
//		free(decoded_path);
//	if (whole_path)
//		free(whole_path);
//	if (evb)
//		evbuffer_free(evb);
//}
/**/

const int ERROR_RESPONSE_SIZE = 512;
void jsonRequestHandler(struct evhttp_request *request, void *arg)
{
//   struct event_base *base = (struct event_base *)arg;

   // Request
//   struct evbuffer *requestBuffer;
//   size_t requestLen;
//   char *requestDataBuffer;

//   json_t *requestJSON;
//   json_error_t error;

   // Error buffer
//   char errorText[ERROR_RESPONSE_SIZE];

   // Process Request
//   requestBuffer = evhttp_request_get_input_buffer(request);
//   requestLen = evbuffer_get_length(requestBuffer);
//
//   requestDataBuffer = (char *)malloc(sizeof(char) * requestLen);
//   memset(requestDataBuffer, 0, requestLen);
//   evbuffer_copyout(requestBuffer, requestDataBuffer, requestLen);

//   printf("%s\n", evhttp_request_uri(request));

//	Json::Reader reader;
//	Json::Value jsonRequest;
//	reader.parse(requestDataBuffer, jsonRequest, false);
	
//	sendJSONResponse(request, jsonRequest);
	
//   requestJSON = json_loadb(requestDataBuffer, requestLen, 0, &error);
//   free(requestDataBuffer);

//	if (requestJSON == NULL)
//	{
//      snprintf(errorText, ERROR_RESPONSE_SIZE, "Input error: on line %d: %s\n", error.line, error.text);
//      sendErrorResponse(request, errorText);
//   } else {
//      // Debug out
//      requestDataBuffer = json_dumps(requestJSON, JSON_INDENT(3));
//      printf("%s\n", requestDataBuffer);
//      free(requestDataBuffer);
//
//      sendJSONResponse(request, requestJSON, base);
//      json_decref(requestJSON);
//   }
}

void sendErrorResponse(struct evhttp_request *request, char *errorText) {
   // Reponse
//   size_t responseLen;
//
//   struct evbuffer *responseBuffer;
//
//   responseLen = strlen(errorText);
//
//   responseBuffer = evbuffer_new();
//
//   // content length to string
//   sprintf(responseHeader, "%d", (int)responseLen);
//
//   evhttp_add_header(request->output_headers, "Content-Type", "text/plain");
//   evhttp_add_header(request->output_headers, "Content-Length", responseHeader);
//
//   evbuffer_add(responseBuffer, errorText, responseLen);
//
//   evhttp_send_reply(request, 400, "Bad JSON", responseBuffer); 
//
//   evbuffer_free(responseBuffer);
}

static const struct table_entry {
	const char *extension;
	const char *content_type;
} content_type_table[] = {
	{ "txt", "text/plain" },
	{ "c", "text/plain" },
	{ "h", "text/plain" },
	{ "html", "text/html" },
	{ "htm", "text/htm" },
	{ "css", "text/css" },
	{ "gif", "image/gif" },
	{ "jpg", "image/jpeg" },
	{ "jpeg", "image/jpeg" },
	{ "png", "image/png" },
	{ "pdf", "application/pdf" },
	{ "ps", "application/postscript" },
	{ NULL, NULL },
};

void sendJSONResponse(struct evhttp_request *request, HTU21DF* htu21df);

/* Try to guess a good content-type for 'path' */
static const char * guess_content_type(const char *path)
{
	const char *last_period, *extension;
	const struct table_entry *ent;
	last_period = strrchr(path, '.');
	if (!last_period || strchr(last_period, '/'))
		goto not_found; /* no exension */
	extension = last_period + 1;
	for (ent = &content_type_table[0]; ent->extension; ++ent) {
		if (!evutil_ascii_strcasecmp(ent->extension, extension))
			return ent->content_type;
	}

not_found:
	return "application/misc";
}

