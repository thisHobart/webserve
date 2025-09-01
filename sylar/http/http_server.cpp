/**
 * @file http_server.cpp
 * @brief Implementation of the HttpServer class.
 *
 * This file contains the logic for handling client connections in the
 * context of an HTTP server.
 */
#include "sylar/http/http_server.h"
#include "sylar/log.h"

namespace sylar {
namespace http {

HttpServer::HttpServer(bool keepalive, IOManager* worker, IOManager* accept_worker)
    : TcpServer(worker, accept_worker), m_isKeepalive(keepalive) {
    m_dispatch.reset(new ServletDispatch);
}

void HttpServer::handleClient(Socket::ptr client) {
    // SYLAR_LOG_INFO(g_logger) << "handleClient " << *client;
    HttpSession::ptr session(new HttpSession(client));
    do {
        auto req = session->recvRequest();
        if(!req) {
            // SYLAR_LOG_WARN(g_logger) << "recv http request fail, errno="
            //     << errno << " errstr=" << strerror(errno)
            //     << " cliet:" << *client;
            break;
        }

        HttpResponse::ptr rsp(new HttpResponse(req->getVersion(),
                    req->isClose() || !m_isKeepalive));

        m_dispatch->handle(req, rsp, session);
        session->sendResponse(rsp);
    } while(m_isKeepalive);
}

}
}
