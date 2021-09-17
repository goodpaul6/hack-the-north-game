#pragma once

#include "vec2.hpp"

namespace htn {

struct World;

void update_particle_emitters(World& world, Vec2f grav_accel);

}  // namespace htn
