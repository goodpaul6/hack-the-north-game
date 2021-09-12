#pragma once

#include <string_view>

#include "formatter.hpp"

#define HTN_LOG_INFO(fmt, ...)                                                    \
    do {                                                                          \
        htn::Logger::instance().log(__FILE__, __LINE__, htn::Logger::Level::INFO, \
                                    htn::format(fmt, ##__VA_ARGS__));             \
    } while (0)

#define HTN_LOG_ERROR(fmt, ...)                                                    \
    do {                                                                           \
        htn::Logger::instance().log(__FILE__, __LINE__, htn::Logger::Level::ERROR, \
                                    htn::format(fmt, ##__VA_ARGS__));              \
    } while (0)

#define HTN_LOG_CRASH(fmt, ...)                                                    \
    do {                                                                           \
        htn::Logger::instance().log(__FILE__, __LINE__, htn::Logger::Level::ERROR, \
                                    htn::format(fmt, ##__VA_ARGS__));              \
        abort();                                                                   \
    } while (0)

namespace htn {

struct Logger {
    enum class Level : uint8_t { DEBUG, INFO, WARNING, ERROR };

    static Logger& instance();

    void configure(Level level, uint32_t mask);
    void log(std::string_view file, int line, Level level, std::string_view msg,
             uint32_t flags = 0);

private:
    Level m_level = Level::INFO;
    uint32_t m_mask = 0;
};

}  // namespace htn
