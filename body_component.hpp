#pragma once

#include <functional>

#include "rect.hpp"
#include "vec2.hpp"

namespace htn {

struct Entity;
struct World;

struct BodyComponent {
    bool solid = true;
    bool affected_by_gravity = true;

    FloatRect rect;
    Vec2f vel;

    size_t collision_sample_count = 10;
};

}  // namespace htn
