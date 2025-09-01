/**
 * @file socket_stream.cpp
 * @brief Implementation of the SocketStream class.
 *
 * This file contains the implementation for reading from and writing to a socket
 * using the unified Stream interface.
 */
#include "sylar/socket_stream.h"

namespace sylar {

SocketStream::SocketStream(Socket::ptr sock, bool owner)
    : m_socket(sock), m_owner(owner) {
}

SocketStream::~SocketStream() {
    if(m_owner && m_socket) {
        m_socket->close();
    }
}

void SocketStream::close() {
    if(m_socket) {
        m_socket->close();
    }
}

int SocketStream::read(void* buffer, size_t length) {
    if(!m_socket) {
        return -1;
    }
    return m_socket->recv(buffer, length);
}

int SocketStream::read(ByteArray::ptr ba, size_t length) {
    // Implementation to read into a ByteArray
    return 0;
}

int SocketStream::write(const void* buffer, size_t length) {
    if(!m_socket) {
        return -1;
    }
    return m_socket->send(buffer, length);
}

int SocketStream::write(ByteArray::ptr ba, size_t length) {
    // Implementation to write from a ByteArray
    return 0;
}

}
