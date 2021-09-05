#pragma once

#include "entity.hpp"

namespace htn {

struct World;
struct Renderer;

void render(World& world, Renderer& r, Entity::ID camera_focus_id);

}  // namespace htn
