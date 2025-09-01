/**
 * @file stream.h
 * @brief Definition of the Stream base class.
 *
 * This file defines a generic Stream interface for unified read and write
 * operations. Other classes, like SocketStream and FileStream, will inherit
 * from this to provide a consistent API for different I/O sources.
 */
#ifndef __SYLAR_STREAM_H__
#define __SYLAR_STREAM_H__

#include <memory>
#include "sylar/bytearray.h"

namespace sylar {

class Stream {
public:
    typedef std::shared_ptr<Stream> ptr;
    virtual ~Stream() {}

    virtual int read(void* buffer, size_t length) = 0;
    virtual int read(ByteArray::ptr ba, size_t length) = 0;
    virtual int write(const void* buffer, size_t length) = 0;
    virtual int write(ByteArray::ptr ba, size_t length) = 0;
    virtual void close() = 0;
};

}

#endif
