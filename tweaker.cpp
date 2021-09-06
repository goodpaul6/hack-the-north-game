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

float Tweaker::find_or_init_float(const std::string& filename, int id, float default_value) {
    auto found_file = m_files.find(filename);

    if (found_file == m_files.end()) {
        long long t = 0;

        if (last_write_time(filename.c_str(), t)) {
            FileValues file{t, {{id, default_value}}};

            m_files.try_emplace(filename, std::move(file));
        }

        return default_value;
    }

    auto found = std::find_if(found_file->second.values.begin(), found_file->second.values.end(),
                              [&](auto& v) { return v.id == id; });

    if (found == found_file->second.values.end()) {
        Value v{id, default_value};

        found_file->second.values.emplace_back(std::move(v));

        return default_value;
    }

    return found->current;
}

void Tweaker::update() {
    for (auto& [filename, file] : m_files) {
        long long t = 0;

        if (last_write_time(filename.c_str(), t) && t > file.last_write_time) {
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
                pos = str.find("HTN_TWEAK_FLOAT", pos);

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

                for (auto& v : file.values) {
                    if (v.id == id_counter) {
                        v.current = value;
                        break;
                    }
                }

                id_counter++;
            }
        }
    }
}

}  // namespace htn
