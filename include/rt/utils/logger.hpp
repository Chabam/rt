#ifndef RT_LOGGER_H
#define RT_LOGGER_H

#include <bitset>
#include <format>
#include <iostream>
#include <sstream>

struct Logger
{
    enum Level
    {
        DEBUG = 1 << 0,
        INFO = 1 << 1,
        WARN = 1 << 2,
        ERROR = 1 << 3
    };

    Logger(const char* category, std::ostream& ostream = std::cout);
    Logger(Logger&& other);
    Logger& operator=(Logger&& other);

    template <typename... Args> void log(Level level, std::string_view text, const Args&... args)
    {
        if (m_enabled_level.to_ulong() & level)
        {
            return;
        }

        constexpr auto WHITE = "\033[0m";
        auto color = level_to_color(level);
        const auto level_text = level_to_text(level);
        std::string formatted_text = std::vformat(text, std::make_format_args(args...));
        std::ostringstream test{};
        m_stream << std::vformat("{}[{}][{}]{} {}",
                                 std::make_format_args(color, level_text, m_category, WHITE, formatted_text))
                 << std::endl;
    }

    template <typename... Args> void debug(std::string_view text, const Args... args)
    {
        return log(Level::DEBUG, text, args...);
    }
    template <typename... Args> void info(std::string_view text, const Args... args)
    {
        return log(Level::INFO, text, args...);
    }
    template <typename... Args> void warn(std::string_view text, const Args... args)
    {
        return log(Level::WARN, text, args...);
    }
    template <typename... Args> void error(std::string_view text, const Args... args)
    {
        return log(Level::ERROR, text, args...);
    }

  private:
    static const char* level_to_text(Level level);
    static const char* level_to_color(Level level);

    const char* m_category;
    std::bitset<sizeof(Level)> m_enabled_level;
    std::ostream& m_stream;
};

#endif // RT_LOGGER_H