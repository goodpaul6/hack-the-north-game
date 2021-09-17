#pragma once

#include "entity.hpp"

namespace htn {

Entity create_block(Vec2f pos);
Entity create_player(Vec2f pos);
Entity create_bullet(Vec2f pos, bool left, bool created_by_player);
Entity create_ground_enemy(Vec2f pos);
Entity create_mushroom(Vec2f pos);

}  // namespace htn
