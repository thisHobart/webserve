#include "sylar/fiber.h"
#include <atomic>
#include <stdexcept>
#include "sylar/config.h"
#include "sylar/log.h"

namespace sylar {

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_count {0};

// The currently running fiber
static thread_local Fiber* t_fiber = nullptr;
// The main fiber of the current thread
static thread_local Fiber::ptr t_threadFiber = nullptr;

// Default stack size, can be configured
static uint32_t g_fiber_stack_size = 128 * 1024; // 128k


class MallocStackAllocator {
public:
    static void* Alloc(size_t size) { return malloc(size); }
    static void Dealloc(void* vp, size_t size) { return free(vp); }
};

using StackAllocator = MallocStackAllocator;

// private constructor
Fiber::Fiber() {
    m_state = EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)) {
        throw std::logic_error("getcontext error");
    }

    ++s_fiber_count;
    // SYLAR_LOG_DEBUG(g_logger) << "Fiber::Fiber main";
}

Fiber::Fiber(std::function<void()> cb, size_t stacksize)
    : m_id(++s_fiber_id), m_cb(cb) {
    ++s_fiber_count;
    m_stacksize = stacksize ? stacksize : g_fiber_stack_size;
    m_stack = StackAllocator::Alloc(m_stacksize);

    if(getcontext(&m_ctx)) {
        throw std::logic_error("getcontext error");
    }
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    makecontext(&m_ctx, &Fiber::MainFunc, 0);
    // SYLAR_LOG_DEBUG(g_logger) << "Fiber::Fiber id=" << m_id;
}

Fiber::~Fiber() {
    --s_fiber_count;
    if(m_stack) {
        // This is a sub-fiber
        StackAllocator::Dealloc(m_stack, m_stacksize);
    } else {
        // This is the main fiber
        SetThis(nullptr);
    }
    // SYLAR_LOG_DEBUG(g_logger) << "Fiber::~Fiber id=" << m_id;
}

void Fiber::reset(std::function<void()> cb) {
    m_cb = cb;
    m_state = INIT;
    if(getcontext(&m_ctx)) {
        throw std::logic_error("getcontext error");
    }
    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    makecontext(&m_ctx, &Fiber::MainFunc, 0);
}

void Fiber::swapIn() {
    SetThis(this);
    m_state = EXEC;
    if(swapcontext(&t_threadFiber->m_ctx, &m_ctx)) {
        throw std::logic_error("swapcontext error");
    }
}

void Fiber::swapOut() {
    SetThis(t_threadFiber.get());
    if(swapcontext(&m_ctx, &t_threadFiber->m_ctx)) {
        throw std::logic_error("swapcontext error");
    }
}

void Fiber::SetThis(Fiber* f) {
    t_fiber = f;
}

Fiber::ptr Fiber::GetThis() {
    if(t_fiber) {
        return t_fiber->shared_from_this();
    }
    // If no fiber is running, create the main fiber
    Fiber::ptr main_fiber(new Fiber);
    t_threadFiber = main_fiber;
    return t_fiber->shared_from_this();
}

void Fiber::YieldToReady() {
    Fiber::ptr cur = GetThis();
    cur->m_state = READY;
    cur->swapOut();
}

void Fiber::YieldToHold() {
    Fiber::ptr cur = GetThis();
    cur->m_state = HOLD;
    cur->swapOut();
}

uint64_t Fiber::TotalFibers() {
    return s_fiber_count;
}

void Fiber::MainFunc() {
    Fiber::ptr cur = GetThis();
    try {
        cur->m_cb();
        cur->m_cb = nullptr;
        cur->m_state = TERM;
    } catch (std::exception& ex) {
        cur->m_state = EXCEPT;
        // SYLAR_LOG_ERROR(g_logger) << "Fiber Except: " << ex.what();
    } catch (...) {
        cur->m_state = EXCEPT;
        // SYLAR_LOG_ERROR(g_logger) << "Fiber Except: unknown";
    }

    auto raw_ptr = cur.get();
    cur.reset();
    raw_ptr->swapOut();
}

}
