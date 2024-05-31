#include <rt/utils/logger.hpp>

const char* Logger::level_to_text(Level level)
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
        throw std::runtime_error("Invalid log level provided");
        break;
    }
}

const char* Logger::level_to_color(Level level)
{
    switch (level)
    {
    case Level::DEBUG:
        return "\x1B[32m"; // GREEN
        break;
    case Level::INFO:
        return "\x1B[34m"; // BLUE
        break;
    case Level::WARN:
        return "\x1B[33m"; // YELLOW
        break;
    case Level::ERROR:
        return "\x1B[31m"; // RED
        break;
    default:
        throw std::runtime_error("Invalid log level provided");
        break;
    }
}