#pragma once

#include "vec2.hpp"

namespace htn {

struct World;
struct Input;

void update_players(World& world, Input& input, Vec2f camera_offset);

}  // namespace htn
