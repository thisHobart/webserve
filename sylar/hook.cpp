#include "sylar/hook.h"
#include <dlfcn.h>
#include "sylar/log.h"

namespace sylar {

static thread_local bool t_hook_enable = false;

bool is_hook_enable() {
    return t_hook_enable;
}

void set_hook_enable(bool flag) {
    t_hook_enable = flag;
}

}

extern "C" {

// Macro to initialize function pointers
#define HOOK_FUN(XX) \
    XX##_fun XX##_f = nullptr;

// List of functions to hook
// HOOK_FUN(sleep);
// HOOK_FUN(socket);

// This struct is used to initialize the function pointers at startup
struct _HookIniter {
    _HookIniter() {
        // #define XX(name) name ## _f = (name ## _fun)dlsym(RTLD_NEXT, #name)
        // XX(sleep);
        // XX(socket);
        // #undef XX
    }
};

static _HookIniter s_hook_initer;


// Actual hook implementations would go here
// For example:
// unsigned int sleep(unsigned int seconds) {
//     if (!sylar::is_hook_enable()) {
//         return sleep_f(seconds);
//     }
//     // ... custom logic using the IOManager's timer
//     return 0;
// }

}
