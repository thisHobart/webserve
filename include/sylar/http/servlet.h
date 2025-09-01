/**
 * @file servlet.h
 * @brief Defines the Servlet interfaces for handling HTTP requests.
 *
 * This file contains the base Servlet class and a ServletDispatch class
 * for routing requests to the appropriate handler based on the URL path.
 * It's inspired by the Java Servlet API.
 */
#ifndef __SYLAR_HTTP_SERVLET_H__
#define __SYLAR_HTTP_SERVLET_H__

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <map>
#include "sylar/http/http.h"
#include "sylar/http/http_session.h"
#include "sylar/mutex.h"

namespace sylar {
namespace http {

class Servlet {
public:
    typedef std::shared_ptr<Servlet> ptr;
    Servlet(const std::string& name) : m_name(name) {}
    virtual ~Servlet() {}
    virtual int32_t handle(HttpRequest::ptr request,
                           HttpResponse::ptr response,
                           HttpSession::ptr session) = 0;
protected:
    std::string m_name;
};

class ServletDispatch : public Servlet {
public:
    typedef std::shared_ptr<ServletDispatch> ptr;
    ServletDispatch();
    int32_t handle(HttpRequest::ptr request,
                   HttpResponse::ptr response,
                   HttpSession::ptr session) override;
    // ... other methods to add/remove servlets
private:
    RWMutex m_mutex;
    // Map from path to servlet, e.g. std::map<std::string, Servlet::ptr>
};

}
}

#endif
