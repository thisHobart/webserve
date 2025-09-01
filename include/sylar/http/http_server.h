/**
 * @file http_server.h
 * @brief Definition of the HttpServer class.
 *
 * This class inherits from TcpServer and specializes it for the HTTP protocol.
 * It handles incoming connections by creating HttpSessions to parse and
 * respond to HTTP requests. It uses a ServletDispatch to route requests.
 */
#ifndef __SYLAR_HTTP_SERVER_H__
#define __SYLAR_HTTP_SERVER_H__

#include "sylar/tcpserver.h"
#include "sylar/http/http_session.h"
#include "sylar/http/servlet.h"

namespace sylar {
namespace http {

class HttpServer : public TcpServer {
public:
    typedef std::shared_ptr<HttpServer> ptr;

    HttpServer(bool keepalive = false,
               sylar::IOManager* worker = sylar::IOManager::GetThis(),
               sylar::IOManager* accept_worker = sylar::IOManager::GetThis());

    ServletDispatch::ptr getServletDispatch() const { return m_dispatch; }
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v; }

protected:
    void handleClient(Socket::ptr client) override;

private:
    bool m_isKeepalive;
    ServletDispatch::ptr m_dispatch;
};

}
}

#endif
