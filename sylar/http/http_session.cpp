/**
 * @file http_session.cpp
 * @brief Implementation of the HttpSession class.
 *
 * This file contains the logic for reading an HTTP request from a client
 * and sending an HTTP response back.
 */
#include "sylar/http/http_session.h"
#include "sylar/http/http_parser.h"

namespace sylar {
namespace http {

HttpSession::HttpSession(Socket::ptr sock, bool owner)
    : SocketStream(sock, owner) {
}

HttpRequest::ptr HttpSession::recvRequest() {
    // Parser logic to read and build a request object
    return nullptr;
}

int HttpSession::sendResponse(HttpResponse::ptr rsp) {
    // Logic to serialize and send a response object
    return 0;
}

}
}
