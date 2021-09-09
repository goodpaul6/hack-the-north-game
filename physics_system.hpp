#pragma once

#include <vector>

#include "rect.hpp"
#include "vec2.hpp"

namespace htn {

struct World;
struct Entity;

void collide_rect(World& world, FloatRect rect, const Entity* entity_to_ignore,
                  std::vector<Entity*>& collisions);

Entity* collide_rect(World& world, FloatRect rect, const Entity* entity_to_ignore);

void update_bodies(World& world, Vec2f grav_accel);

}  // namespace htn
