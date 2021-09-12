#pragma once

#include "entity.hpp"

namespace htn {

struct Assets;

Entity create_block(Assets& assets, Vec2f pos);
Entity create_player(Assets& assets, Vec2f pos);
Entity create_bullet(Assets& assets, Vec2f pos, bool left, bool created_by_player);
Entity create_ground_enemy(Assets& assets, Vec2f pos);
Entity create_mushroom(Assets& assets, Vec2f pos);
Entity create_explosion(Vec2f pos);

}  // namespace htn
