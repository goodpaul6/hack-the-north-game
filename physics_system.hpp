#pragma once

#include "vec2.hpp"

namespace htn {

struct World;

void simulate_physics(World& world, Vec2f grav_accel);

}  // namespace htn
