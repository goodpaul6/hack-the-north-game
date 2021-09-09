#pragma once

#include "rect.hpp"
#include "vec2.hpp"

namespace htn {

struct World;
struct Entity;

Entity* collide_rect(World& world, FloatRect rect, const Entity* entity_to_ignore);

void update_bodies(World& world, Vec2f grav_accel);

}  // namespace htn
