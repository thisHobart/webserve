#ifndef __SYLAR_MUTEX_H__
#define __SYLAR_MUTEX_H__

#include <thread>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>

namespace sylar {

// Scoped lock implementation for RAII
template<class T>
struct ScopedLockImpl {
public:
    ScopedLockImpl(T& mutex)
        :m_mutex(mutex) {
        m_mutex.lock();
        m_locked = true;
    }

    ~ScopedLockImpl() {
        unlock();
    }

    void lock() {
        if(!m_locked) {
            m_mutex.lock();
            m_locked = true;
        }
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }
private:
    T& m_mutex;
    bool m_locked;
};

// Semaphore Wrapper
class Semaphore {
public:
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();
private:
    sem_t m_semaphore;
};

// Mutex Wrapper
class Mutex {
public:
    typedef ScopedLockImpl<Mutex> Lock;
    Mutex();
    ~Mutex();

    void lock();
    void unlock();
private:
    pthread_mutex_t m_mutex;
};

// Read-Write Mutex Wrapper
class RWMutex {
public:
    typedef ScopedLockImpl<RWMutex> ReadLock;
    typedef ScopedLockImpl<RWMutex> WriteLock;

    RWMutex();
    ~RWMutex();

    void rdlock();
    void wrlock();
    void unlock();
private:
    pthread_rwlock_t m_lock;
};


// Spinlock Wrapper
class Spinlock {
public:
    typedef ScopedLockImpl<Spinlock> Lock;
    Spinlock();
    ~Spinlock();

    void lock();
    void unlock();
private:
    pthread_spinlock_t m_mutex;
};

}

#endif
