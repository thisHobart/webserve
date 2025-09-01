#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

// Stream-style logging macro
#define SYLAR_LOG_INFO(logger) sylar::LogEventWrap(logger, sylar::LogEvent::ptr(new sylar::LogEvent(sylar::LogLevel::INFO, __FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0), "thread_name"))).getSS()

// Formatted logging macro
#define SYLAR_LOG_FMT_INFO(logger, fmt, ...) sylar::LogEventWrap(logger, sylar::LogEvent::ptr(new sylar::LogEvent(sylar::LogLevel::INFO, __FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0), "thread_name"))).getEvent()->format(fmt, __VA_ARGS__)


namespace sylar {

// Forward declarations
class Logger;

// Log Level
class LogLevel {
public:
    enum Level {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* ToString(LogLevel::Level level);
};

// Log Event
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(LogLevel::Level level, const char* file, int32_t line, uint32_t elapse,
             uint32_t thread_id, uint32_t fiber_id, uint64_t time, const std::string& thread_name);

    const char* getFile() const { return m_file; }
    int32_t getLine() const { return m_line; }
    // ... other getters ...

    std::string getContent() const;
    std::stringstream& getSS();
    void format(const char* fmt, ...);

private:
    const char* m_file = nullptr;   // Filename
    int32_t m_line = 0;             // Line number
    uint32_t m_elapse = 0;          // Elapsed time (ms) from program start
    uint32_t m_threadId = 0;        // Thread ID
    uint32_t m_fiberId = 0;         // Fiber ID
    uint64_t m_time;                // Timestamp
    std::string m_threadName;       // Thread Name
    std::stringstream m_ss;         // Log content stream
    LogLevel::Level m_level;
};

// Log Event Wrapper for stream-style logging
class LogEventWrap {
public:
    LogEventWrap(Logger* logger, LogEvent::ptr e);
    ~LogEventWrap();
    LogEvent::ptr getEvent() const { return m_event; }
    std::stringstream& getSS();
private:
    Logger* m_logger;
    LogEvent::ptr m_event;
};


// Log Formatter
class LogFormatter {
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(LogEvent::ptr event);
private:
    // ... formatter items ...
    std::string m_pattern;
};

// Log Appender
class LogAppender {
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender() {}

    virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
    void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
    LogFormatter::ptr getFormatter() const { return m_formatter; }
protected:
    LogLevel::Level m_level = LogLevel::DEBUG;
    LogFormatter::ptr m_formatter;
};

// Logger
class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level val) { m_level = val; }

private:
    std::string m_name;
    LogLevel::Level m_level;
    std::list<LogAppender::ptr> m_appenders;
};

// Helper functions to be implemented in .cpp
uint32_t GetThreadId();
uint32_t GetFiberId();

}

#endif
