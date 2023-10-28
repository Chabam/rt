#include <iostream>
#include <sstream>
#include <string>

class Logger
{
  public:
    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };
    Logger(Level level = Level::DEBUG);
    ~Logger();

    std::ostringstream &operator<<(const char *text);
    std::ostringstream &operator<<(const std::ostringstream &stream);

  private:
    void flush();
    bool m_debug;
    Level m_level;
    std::ostringstream m_stream;
    static const char *levelToText(Level level);
};

#define LOG(text, level)                                                                                               \
    {                                                                                                                  \
        Logger logger(level);                                                                                          \
        logger << text;                                                                                                \
    }                                                                                                                  \
    static_assert(true, "")
#define LOG_DEBUG(text) LOG(text, Logger::Level::DEBUG)
#define LOG_INFO(text) LOG(text, Logger::Level::INFO)
#define LOG_WARN(text) LOG(text, Logger::Level::WARN)
#define LOG_ERROR(text) LOG(text, Logger::Level::ERROR)