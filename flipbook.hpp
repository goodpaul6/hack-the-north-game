#pragma once

#include <vector>

#include "rect.hpp"
#include "vec2.hpp"

namespace htn {

struct Flipbook {
    float frame_time = 0;
    std::vector<IntRect> frames;
};

}  // namespace htn
