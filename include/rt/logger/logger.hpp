#ifndef RT_LOGGER_H
#define RT_LOGGER_H

#include <sstream>

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
    Logger(Level level);
    Logger(Logger&& other) noexcept;
    ~Logger();

    template <typename T> Logger&& operator<<(const T& text)
    {
        m_stream << text;

        return std::move(*this);
    }

    static Logger debug(const char* text);
    static Logger info(const char* text);
    static Logger warn(const char* text);
    static Logger error(const char* text);

  private:
    void flush();
    Level m_level;
    std::ostringstream m_stream;
    static const char* levelToText(Level level);
};

#endif // RT_LOGGER_H