#pragma once

#include <optional>

#include "entity.hpp"

namespace htn {

struct World;
struct Renderer;

struct RenderSystem {
    void update_camera_offset(World& world, Vec2f view_size, Entity::ID camera_focus_id);

    void render(World& world, Renderer& r, bool debug_bodies, float progress_between_frames);

    Vec2f camera_offset() const;

private:
    std::optional<Vec2f> m_last_camera_offset;
};

}  // namespace htn
