/**
 * @file http.h
 * @brief Defines the basic structures for HTTP, like HttpRequest and HttpResponse.
 *
 * This file contains the class definitions for representing HTTP requests
 * and responses, including methods, status codes, headers, and body.
 */
#ifndef __SYLAR_HTTP_H__
#define __SYLAR_HTTP_H__

#include <memory>
#include <string>
#include <map>
#include <iostream>

namespace sylar {
namespace http {

// Define HttpRequest and HttpResponse classes here

class HttpRequest {
public:
    typedef std::shared_ptr<HttpRequest> ptr;
    // ...
};

class HttpResponse {
public:
    typedef std::shared_ptr<HttpResponse> ptr;
    // ...
};

}
}

#endif
