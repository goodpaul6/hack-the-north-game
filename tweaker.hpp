#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#ifndef HTN_BAKE_TWEAKS

#define HTN_TWEAK_FLOAT(value) \
    (htn::Tweaker::instance().find_or_init_float(__FILE__, __COUNTER__, (value)))

#else

#define HTN_TWEAK_FLOAT(value) (value)

#endif

namespace htn {

struct Tweaker {
    static Tweaker& instance();

    float find_or_init_float(const std::string& filename, int id, float default_value);

    void update();

private:
    struct Value {
        int id = 0;
        float current = 0;
    };

    struct FileValues {
        long long last_write_time = 0;
        std::vector<Value> values;
    };

    std::unordered_map<std::string, FileValues> m_files;
};

}  // namespace htn
