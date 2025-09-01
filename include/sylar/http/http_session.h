/**
 * @file http_session.h
 * @brief Defines the HttpSession class for server-side HTTP communication.
 *
 * An HttpSession object represents a connection from a client to our server.
 * It uses a SocketStream to handle reading requests and writing responses.
 */
#ifndef __SYLAR_HTTP_SESSION_H__
#define __SYLAR_HTTP_SESSION_H__

#include "sylar/socket_stream.h"
#include "sylar/http/http.h"

namespace sylar {
namespace http {

class HttpSession : public SocketStream {
public:
    typedef std::shared_ptr<HttpSession> ptr;
    HttpSession(Socket::ptr sock, bool owner = true);

    HttpRequest::ptr recvRequest();
    int sendResponse(HttpResponse::ptr rsp);
};

}
}

#endif
