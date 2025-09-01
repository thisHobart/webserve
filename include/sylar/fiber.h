#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include <functional>
#include <ucontext.h>

namespace sylar {

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State {
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };

private:
    // Private constructor to force use of shared_ptr
    Fiber();

public:
    Fiber(std::function<void()> cb, size_t stacksize = 0);
    ~Fiber();

    // Reset a finished fiber for reuse
    void reset(std::function<void()> cb);

    // Switch to the current fiber
    void swapIn();

    // Switch out of the current fiber
    void swapOut();

    uint64_t getId() const { return m_id; }
    State getState() const { return m_state; }

public:
    // Set the current running fiber
    static void SetThis(Fiber* f);

    // Get the current running fiber
    static Fiber::ptr GetThis();

    // Yield the execution of the current fiber
    static void YieldToReady();
    static void YieldToHold();

    // Total number of fibers
    static uint64_t TotalFibers();

    // Main execution function for fibers
    static void MainFunc();

private:
    uint64_t m_id = 0;
    uint32_t m_stacksize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;

    std::function<void()> m_cb;
};

}

#endif
