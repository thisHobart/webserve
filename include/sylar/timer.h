#ifndef __SYLAR_TIMER_H__
#define __SYLAR_TIMER_H__

#include <memory>

namespace sylar {

class TimerManager;

class Timer {
    friend class TimerManager;
public:
    typedef std::shared_ptr<Timer> ptr;
    // placeholder for Timer class
};

class TimerManager {
public:
    // placeholder for TimerManager class
};

}

#endif
