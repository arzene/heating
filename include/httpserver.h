#pragma once

#include <event2/http.h>

void environmentRequestHandler(struct evhttp_request *req, void *arg);
static void send_document_cb(struct evhttp_request *req, void *arg);

void jsonRequestHandler(struct evhttp_request *request, void *arg);
