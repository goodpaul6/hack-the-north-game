#pragma once

#include "entity.hpp"

namespace htn {

struct Assets;

Entity create_block(Assets& a, Vec2f pos);
Entity create_player(Assets& a, Vec2f pos);
Entity create_bullet(Assets& a, Vec2f pos, bool left, bool created_by_player);

}  // namespace htn
