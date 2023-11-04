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
    Logger(Level level);
    Logger(Logger &&other);
    ~Logger();

    Logger &&operator<<(const char *text);
    Logger &&operator<<(const std::ostringstream &stream);

    static Logger debug(const char *text);
    static Logger info(const char *text);
    static Logger warn(const char *text);
    static Logger error(const char *text);

  private:
    void flush();
    Level m_level;
    std::ostringstream m_stream;
    static const char *levelToText(Level level);
};