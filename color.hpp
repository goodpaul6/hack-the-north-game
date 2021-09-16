#pragma once

#include <cstdint>

#include "tigr.h"

namespace htn {

struct Color {
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 0xff;

    operator TPixel() const { return {r, g, b, a}; }
};

inline Color BLACK;
inline Color GREY{0x7f, 0x7f, 0x7f, 0xff};
inline Color DARK_GREY{0x2f, 0x2f, 0x2f, 0xff};
inline Color WHITE{0xff, 0xff, 0xff, 0xff};
inline Color TRANSPARENT{0, 0, 0, 0};
inline Color RED{0xff, 0, 0, 0xff};
inline Color GREEN{0, 0xff, 0, 0xff};
inline Color BLUE{0, 0, 0xff, 0xff};
inline Color BROWN{245, 222, 179, 0xff};

inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

}  // namespace htn
