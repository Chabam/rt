#include <assert.h>
#include <rt/logger/logger.h>

Logger::Logger(Level level) : m_level(level)
{
}

Logger::~Logger()
{
    flush();
}

const char *Logger::levelToText(Level level)
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
        break;
    }
}

std::ostringstream &Logger::operator<<(const char *text)
{
    m_stream << text;
    return m_stream;
}

std::ostringstream &Logger::operator<<(const std::ostringstream &stream)
{
    m_stream << stream.str();
    return m_stream;
}

void Logger::flush()
{
    static const char *WHITE = "\033[0m";
    const char *color = WHITE;
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