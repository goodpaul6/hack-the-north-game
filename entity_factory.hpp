#pragma once

#include "entity.hpp"

namespace htn {

struct Assets;

Entity create_block(Assets& a, Vec2f pos);
Entity create_player(Assets& a, Vec2f pos);

}  // namespace htn
