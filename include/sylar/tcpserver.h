/**
 * @file tcpserver.h
 * @brief Definition of the TcpServer class.
 *
 * This file defines a generic TCP server class that simplifies the process
 * of binding to an address, listening for connections, and handling new clients.
 * Users should inherit from this class to implement their specific server logic.
 */
#ifndef __SYLAR_TCPSERVER_H__
#define __SYLAR_TCPSERVER_H__

#include <memory>
#include <functional>
#include "sylar/socket.h"
#include "sylar/iomanager.h"

namespace sylar {

class TcpServer : public std::enable_shared_from_this<TcpServer> {
public:
    typedef std::shared_ptr<TcpServer> ptr;

    TcpServer(sylar::IOManager* worker = sylar::IOManager::GetThis(),
              sylar::IOManager* accept_worker = sylar::IOManager::GetThis());
    virtual ~TcpServer();

    virtual bool bind(sylar::Address::ptr addr);
    virtual bool start();
    virtual void stop();

protected:
    virtual void handleClient(Socket::ptr client);

private:
    // placeholder for private members
};

}

#endif
