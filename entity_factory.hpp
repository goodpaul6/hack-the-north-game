#pragma once

#include "entity.hpp"

namespace htn {

struct Assets;

Entity create_block(Assets& a, Vec2f pos);
Entity create_player(Assets& a, Vec2f pos);
Entity create_bullet(Assets& a, Vec2f pos, bool left, bool ignore_collision_with_platformer);

}  // namespace htn
