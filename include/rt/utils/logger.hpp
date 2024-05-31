#ifndef RT_LOGGER_H
#define RT_LOGGER_H

#include <format>
#include <iostream>

struct Logger
{
    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    template <typename... Args> static void log(Level level, std::string_view text, const Args&... args)
    {
        static constexpr auto WHITE = "\033[0m";
        auto color = level_to_color(level);
        const auto level_text = level_to_text(level);
        std::string formatted_text = std::vformat(text, std::make_format_args(args...));
        std::cout << std::vformat("{}[{}]{} {}", std::make_format_args(color, level_text, WHITE, formatted_text))
                  << std::endl;
    }

    template <typename... Args> static void debug(std::string_view text, const Args... args)
    {
        return log(Level::DEBUG, text, args...);
    }
    template <typename... Args> static void info(std::string_view text, const Args... args)
    {
        return log(Level::INFO, text, args...);
    }
    template <typename... Args> static void warn(std::string_view text, const Args... args)
    {
        return log(Level::WARN, text, args...);
    }
    template <typename... Args> static void error(std::string_view text, const Args... args)
    {
        return log(Level::ERROR, text, args...);
    }

  private:
    static const char* level_to_text(Level level);
    static const char* level_to_color(Level level);
};

#endif // RT_LOGGER_H