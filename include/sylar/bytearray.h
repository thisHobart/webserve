#ifndef __SYLAR_BYTEARRAY_H__
#define __SYLAR_BYTEARRAY_H__

#include <memory>
#include <string>
#include <stdint.h>
#include <sys/types.h>
#include <vector>

namespace sylar {

class ByteArray {
public:
    typedef std::shared_ptr<ByteArray> ptr;

    ByteArray(size_t base_size = 4096);
    ~ByteArray();

    // Placeholder for ByteArray methods
    // (e.g., write_int32, read_int32, write_string, etc.)
};

}

#endif
