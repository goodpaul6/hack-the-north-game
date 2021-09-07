#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

#ifndef HTN_BAKE_TWEAKS

#define HTN_TWEAK(value) (htn::Tweaker::instance().find_or_init(__FILE__, __COUNTER__, (value)))

#else

#define HTN_TWEAK(value) (value)

#endif

namespace htn {

struct Tweaker {
    static Tweaker& instance();

    float find_or_init(const std::string& filename, int id, float default_value);

    void update();

private:
    struct FileValues {
        long long last_write_time = 0;
        std::unordered_map<int, float> values;
    };

    std::unordered_map<std::string, FileValues> m_files;

    Tweaker() = default;
};

}  // namespace htn
