#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string>
#include <iostream>
#include <string.h>
#include <event.h>

#include <httpserver.h>

#include <I2CDevice.h>
#include <HTU21DF.h>
#include <HttpGetResponse.h>

#define DAEMON_NAME "Heat Control"

using namespace std;

bool SetupDaemon()
{
	cout << "[1]" << endl;
	//Set our Logging Mask and open the Log
    setlogmask(LOG_UPTO(LOG_NOTICE));
    
	openlog(DAEMON_NAME, LOG_CONS | LOG_NDELAY | LOG_PERROR | LOG_PID, LOG_USER);

    syslog(LOG_INFO, "Entering Daemon");

    pid_t pid, sid;

   //Fork the Parent Process
    pid = fork();

    if (pid < 0)
	{
		cout << "[pid < 0]" << endl;
		exit(EXIT_FAILURE);
	}

    //We got a good pid, Close the Parent Process
    if (pid > 0)
	{
		cout << "[pid > 0]" << endl;
		exit(EXIT_SUCCESS);
	}

    //Change File Mask
    umask(0);

    //Create a new Signature Id for our child
    sid = setsid();
    if (sid < 0)
	{
		cout << "[sid < 0]" << endl;

		exit(EXIT_FAILURE);
	}

    //Change Directory
    //If we cant find the directory we exit with failure.
    if ((chdir("/")) < 0)
	{
		exit(EXIT_FAILURE);
	}

    //Close Standard File Descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
	return true;
}

typedef struct
{
	HTU21DF* htu21df;
	struct event *timeout;
} Timeout_cb_args;

static void timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	Timeout_cb_args* timeout_cb_args = (Timeout_cb_args*)arg;

//	if (! event_is_persistent) {
	syslog(LOG_INFO, "Temperature aquired");
	cout << timeout_cb_args->htu21df->GetTemperature() << endl;
	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = 2;
	event_add(timeout_cb_args->timeout, &tv);
//	}
}

void SetupHttpServer()
{}

char uri_root[512];

int main(int argc, char **argv)
{
//	if (SetupDaemon())
//		return 1;
		
	string deviceFilename("/dev/i2c-1");
	int bus = open(deviceFilename.c_str(), O_RDWR);
	
//	if (bus < 0)
//	{
//        cout << "bus < 0" << endl;
//		return 1;
//	}

	struct event timeout;
	struct timeval tv;
	struct event_base *base;

	/* Initalize the event library */
	base = event_base_new();

	/* Initalize one event */

	I2CDevice i2cDevice(bus, 0x40);
	HTU21DF htu21df(&i2cDevice);

	Timeout_cb_args timeout_cb_args;
	timeout_cb_args.htu21df = &htu21df;
	timeout_cb_args.timeout = &timeout;
	
	event_assign(&timeout, base, -1, /*EV_PERSIST*/0, timeout_cb, (void*) &timeout_cb_args);

	evutil_timerclear(&tv);
	tv.tv_sec = 5;
	event_add(&timeout, &tv);

/*
 * 	HTTP
 *
 */
	short            http_port = 8000;
	const char      *http_addr = "127.0.0.1";
	struct evhttp *http_server = NULL;

	http_server = evhttp_new(base);
	
	evhttp_bind_socket_with_handle(http_server, http_addr, http_port);

	JsonTemperatureResponse jsonTemperatureResponse(&htu21df);
	evhttp_set_cb(http_server, "/temperature", environmentRequestHandler, &jsonTemperatureResponse);

	fprintf(stderr, "Server started on %s port %d\n", http_addr, http_port);
	
////////////////////////
//	struct evhttp *http;
//	struct evhttp_bound_socket *handle;
//
//	ev_uint16_t port = 0;

//	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
//		return (1);

//	base = event_base_new();

	/* Create a new evhttp object to handle requests. */
//	http = evhttp_new(base);
//
//	if (!http)
//	{
//		fprintf(stderr, "couldn't create evhttp. Exiting.\n");
//		return 1;
//	}

	/* The /dump URI will dump all requests to stdout and say 200 ok. */
//	evhttp_set_cb(http, "/dump", dump_request_cb, NULL);

	/* We want to accept arbitrary requests, so we need to set a "generic"
	 * cb.  We can also add callbacks for specific paths. */
//	evhttp_set_gencb(http, send_document_cb, argv[1]);

	/* Now we tell the evhttp what port to listen on */
//	port = 8080;
//	handle = evhttp_bind_socket_with_handle(http, "0.0.0.0", port);
//	if (!handle) {
//		fprintf(stderr, "couldn't bind to port %d. Exiting.\n",
//		    (int)port);
//		return 1;
//	}
//
//	{
//		/* Extract and display the address we're listening on. */
//		struct sockaddr_storage ss;
//		evutil_socket_t fd;
//		ev_socklen_t socklen = sizeof(ss);
//		char addrbuf[128];
//		void *inaddr;
//		const char *addr;
//		int got_port = -1;
//		fd = evhttp_bound_socket_get_fd(handle);
//		memset(&ss, 0, sizeof(ss));
//		if (getsockname(fd, (struct sockaddr *)&ss, &socklen)) {
//			perror("getsockname() failed");
//			return 1;
//		}
//		if (ss.ss_family == AF_INET) {
//			got_port = ntohs(((struct sockaddr_in*)&ss)->sin_port);
//			inaddr = &((struct sockaddr_in*)&ss)->sin_addr;
//		} else if (ss.ss_family == AF_INET6) {
//			got_port = ntohs(((struct sockaddr_in6*)&ss)->sin6_port);
//			inaddr = &((struct sockaddr_in6*)&ss)->sin6_addr;
//		} else {
//			fprintf(stderr, "Weird address family %d\n",
//			    ss.ss_family);
//			return 1;
//		}
//		addr = evutil_inet_ntop(ss.ss_family, inaddr, addrbuf,
//		    sizeof(addrbuf));
//		if (addr) {
//			printf("Listening on %s:%d\n", addr, got_port);
//			evutil_snprintf(uri_root, sizeof(uri_root),
//			    "http://%s:%d",addr,got_port);
//		} else {
//			fprintf(stderr, "evutil_inet_ntop failed\n");
//			return 1;
//		}
//	}

//	event_base_dispatch(base);

	///////////////////////
	event_base_dispatch(base);
	 
#ifndef DEBUG
	close(bus);
#endif

	closelog();
	return 0;
}

