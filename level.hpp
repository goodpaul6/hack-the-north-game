#pragma once

#include "render_system.hpp"
#include "sand.hpp"
#include "tilemap.hpp"
#include "world.hpp"

namespace htn {

struct Renderer;
struct Input;
struct Assets;

struct Level {
    Level();

    void update(float dt);
    void fixed_update(Input& input, Vec2f view_size);
    void render(Renderer& renderer, float progress_between_frames);

private:
    World m_world;
    Sand m_sand;
    RenderSystem m_render_system;
};

}  // namespace htn
