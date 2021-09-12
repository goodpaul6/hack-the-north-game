#include "logger.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

namespace htn {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::configure(Level level, uint32_t mask) {
    m_level = level;
    m_mask = mask;
}

void Logger::log(std::string_view file, int line, Level level, std::string_view msg,
                 uint32_t flags) {
    auto level_value = static_cast<uint8_t>(level);

    if (level_value < static_cast<uint8_t>(m_level)) {
        return;
    }

    if (level_value < static_cast<uint8_t>(Level::ERROR) && m_mask != 0 && (flags & m_mask) == 0) {
        return;
    }

    using namespace std::chrono;

    auto cur_time = system_clock::to_time_t(system_clock::now());
    auto tm = std::localtime(&cur_time);
    char buf[128];

    std::strftime(buf, sizeof(buf), "%T", tm);

    auto& stream = ([&]() -> std::ostream& {
        if (level == Level::ERROR) {
            return std::cerr;
        }

        return std::cout;
    })();

    stream << '[' << buf << "] ";

    switch (level) {
        case Level::DEBUG:
            stream << "DEBUG ";
            break;
        case Level::INFO:
            stream << "INFO ";
            break;
        case Level::WARNING:
            stream << "WARNING ";
            break;
        case Level::ERROR:
            stream << "ERROR ";
            break;
    }

    if (auto pos = file.find_last_of("/\\"); pos != std::string_view::npos) {
        file = file.substr(pos + 1);
    }

    stream << file << ":" << line << '\t' << msg << '\n';
}

}  // namespace htn
