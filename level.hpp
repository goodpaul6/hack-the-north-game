#pragma once

#include "render_system.hpp"
#include "tilemap.hpp"
#include "world.hpp"

namespace htn {

struct Renderer;
struct Input;
struct Assets;

struct Level {
    Level(const std::string& filename);

    void update(float dt);
    void fixed_update(Input& input, Vec2f view_size);
    void render(Renderer& renderer, float progress_between_frames);

private:
    World m_world;
    Tilemap m_tilemap;
    RenderSystem m_render_system;

    Entity::ID m_player_id = Entity::INVALID_ID;
};

}  // namespace htn
