#pragma once

#include <optional>

#include "entity.hpp"

namespace htn {

struct World;
struct Renderer;

struct RenderSystem {
    void render(World& world, Renderer& r, Entity::ID camera_focus_id, bool debug_bodies,
                float progress_between_frames);

private:
    std::optional<Vec2f> m_last_camera_offset;
};

}  // namespace htn
