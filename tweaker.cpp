#include "tweaker.hpp"

#include <algorithm>
#include <fstream>
#include <streambuf>

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

#else

#include <sys/stat.h>
#include <sys/types.h>

#endif

#include "logger.hpp"

namespace {

bool last_write_time(const char* filename, long long& time) {
#ifdef _WIN32
    FILETIME c, a, w;
    HANDLE hFile =
        CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return false;
    }

    if (!GetFileTime(hFile, &c, &a, &w)) {
        return false;
    }

    time = ((long long)w.dwHighDateTime << 32 | w.dwLowDateTime);

    CloseHandle(hFile);

    return true;
#else
    struct stat buf;

    int r = stat(filename, &buf);

    if (r < 0) {
        return false;
    }

    time = buf.st_mtim.tv_sec;

    return true;
#endif
}

}  // namespace
namespace htn {

Tweaker& Tweaker::instance() {
    static Tweaker instance;
    return instance;
}

float Tweaker::find_or_init(const std::string& filename, int id, float default_value) {
    auto& file = m_files[filename];

    auto found = file.values.find(id);

    if (found == file.values.end()) {
        return (file.values[id] = default_value);
    }

    return found->second;
}

void Tweaker::update() {
    for (auto& [filename, file] : m_files) {
        long long t = 0;

        if (!last_write_time(filename.c_str(), t)) {
            continue;
        }

        if (t <= file.last_write_time) {
            continue;
        }

        HTN_LOG_INFO("Reloading tweakers for {}", filename.c_str());

        file.last_write_time = t;

        std::ifstream fs{filename};
        std::string str;

        fs.seekg(0, std::ios::end);
        str.reserve(fs.tellg());
        fs.seekg(0, std::ios::beg);

        str.assign(std::istreambuf_iterator<char>{fs}, std::istreambuf_iterator<char>{});

        auto pos = 0u;

        int id_counter = 0;

        for (;;) {
            pos = str.find("HTN_TWEAK", pos);

            if (pos == std::string::npos) {
                break;
            }

            pos = str.find('(', pos);

            if (pos == std::string::npos) {
                break;
            }

            auto end_pos = str.find(')', pos);

            if (end_pos == std::string::npos) {
                break;
            }

            auto s = str.substr(pos + 1, end_pos - pos + 1);
            auto value = std::stof(s);

            file.values[id_counter] = value;

            id_counter++;
        }
    }
}

}  // namespace htn
