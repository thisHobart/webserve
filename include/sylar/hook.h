#ifndef __SYLAR_HOOK_H__
#define __SYLAR_HOOK_H__

#include <unistd.h>

namespace sylar {

bool is_hook_enable();
void set_hook_enable(bool flag);

}

extern "C" {

// Placeholders for hooked function signatures
// e.g., sleep
typedef unsigned int (*sleep_fun)(unsigned int seconds);
extern sleep_fun sleep_f;

// e.g., socket
typedef int (*socket_fun)(int domain, int type, int protocol);
extern socket_fun socket_f;

// ... and so on for read, write, connect, accept, etc.

}

#endif
