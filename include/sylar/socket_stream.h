/**
 * @file socket_stream.h
 * @brief Definition of the SocketStream class.
 *
 * This class implements the Stream interface for a Socket, allowing for
 * stream-based reading and writing on a network connection.
 */
#ifndef __SYLAR_SOCKET_STREAM_H__
#define __SYLAR_SOCKET_STREAM_H__

#include "sylar/stream.h"
#include "sylar/socket.h"

namespace sylar {

class SocketStream : public Stream {
public:
    typedef std::shared_ptr<SocketStream> ptr;

    SocketStream(Socket::ptr sock, bool owner = true);
    ~SocketStream();

    int read(void* buffer, size_t length) override;
    int read(ByteArray::ptr ba, size_t length) override;
    int write(const void* buffer, size_t length) override;
    int write(ByteArray::ptr ba, size_t length) override;
    void close() override;

protected:
    Socket::ptr m_socket;
    bool m_owner;
};

}

#endif
