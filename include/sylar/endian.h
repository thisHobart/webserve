/**
 * @file endian.h
 * @brief Utilities for handling byte order (endianness).
 *
 * This file provides functions to convert between big-endian and little-endian
 * formats, which is crucial for network programming and consistent serialization.
 */
#ifndef __SYLAR_ENDIAN_H__
#define __SYLAR_ENDIAN_H__

#include <byteswap.h>
#include <stdint.h>

namespace sylar {

// Placeholder for endian conversion functions
template<class T>
T byteswap(T value) {
    return value; // Should be implemented with __builtin_bswap or similar
}

}

#endif
