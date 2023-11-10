#include "logger.h"

#include <assert.h>
#include <iostream>

Logger::Logger(Level level)
    : m_level(level)
{
}

Logger::Logger(Logger&& other) noexcept
    : m_level(other.m_level)
    , m_stream(std::move(other.m_stream))
{
}

Logger::~Logger()
{
    if (m_stream.tellp() != 0)
    {
        flush();
    }
}

template <typename T> Logger logImpl(const T& text, Logger::Level level)
{
    return Logger(level) << text;
}

Logger Logger::debug(const char* text)
{
    return logImpl(text, Level::DEBUG);
}

Logger Logger::info(const char* text)
{
    return logImpl(text, Level::INFO);
}

Logger Logger::warn(const char* text)
{
    return logImpl(text, Level::WARN);
}

Logger Logger::error(const char* text)
{
    return logImpl(text, Level::ERROR);
}

const char* Logger::levelToText(Level level)
{
    switch (level)
    {
    case Level::DEBUG:
        return "DEBUG";
        break;
    case Level::INFO:
        return "INFO";
        break;
    case Level::WARN:
        return "WARN ";
        break;
    case Level::ERROR:
        return "ERROR";
        break;
    default:
        // Should not happen
        assert(false);
        return " ";
        break;
    }
}

void Logger::flush()
{
    static const char* WHITE = "\033[0m";
    const char* color = WHITE;
    switch (m_level)
    {
    case Level::DEBUG:
        color = "\x1B[32m"; // GREEN
        break;
    case Level::INFO:
        color = "\x1B[34m"; // BLUE
        break;
    case Level::WARN:
        color = "\x1B[33m"; // YELLOW
        break;
    case Level::ERROR:
        color = "\x1B[31m"; // RED
        break;
    default:
        break;
    }

    std::cout << color << "[ " << levelToText(m_level) << " ] " << WHITE << m_stream.str() << std::endl;
}