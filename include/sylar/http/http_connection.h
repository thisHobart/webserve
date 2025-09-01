/**
 * @file http_connection.h
 * @brief Defines the HttpConnection class for client-side HTTP communication.
 *
 * This class is used to connect to a server, send HTTP requests, and receive
 * HTTP responses. It acts as an HTTP client.
 */
#ifndef __SYLAR_HTTP_CONNECTION_H__
#define __SYLAR_HTTP_CONNECTION_H__

#include "sylar/socket_stream.h"
#include "sylar/http/http.h"

namespace sylar {
namespace http {

class HttpConnection : public SocketStream {
public:
    typedef std::shared_ptr<HttpConnection> ptr;

    // Static method to perform a GET request
    static HttpResponse::ptr DoGet(const std::string& url, uint64_t timeout_ms);
};

}
}

#endif
