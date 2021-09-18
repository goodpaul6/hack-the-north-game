#include "level.hpp"

#include "assets.hpp"
#include "bullet_system.hpp"
#include "color.hpp"
#include "entity.hpp"
#include "entity_factory.hpp"
#include "flipbook_system.hpp"
#include "ground_mover_system.hpp"
#include "health_system.hpp"
#include "image.hpp"
#include "input.hpp"
#include "particle_emitter_system.hpp"
#include "physics_system.hpp"
#include "platformer_system.hpp"
#include "player_system.hpp"
#include "remove_after_duration_system.hpp"
#include "render_system.hpp"
#include "renderer.hpp"
#include "tilemap.hpp"
#include "time.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

Level::Level() : m_sand{320, 180} {
    m_world.add_next_frame(create_player({100, 0}));

    for (int i = 0; i < 10; ++i) {
        m_world.add_next_frame(create_block({100 + i * 16, 150}));
    }

    m_world.add_next_frame(create_block({100, 150 - 16}));
    m_world.add_next_frame(create_block({100 + 160 - 16, 150 - 16}));
}

void Level::update(float dt) {
    m_world.update();

    update_flipbooks(m_world, dt);
    update_health(m_world, dt);
    update_remove_after_duration(m_world, dt);
}

void Level::fixed_update(Input& input, Vec2f view_size) {
    Vec2f grav_accel{0, HTN_TWEAK(0.1)};

    update_bodies(m_world, grav_accel);
    update_platformers(m_world);
    update_players(m_world, input);

    for (int y = 0; y < m_sand.height(); ++y) {
        for (int x = 0; x < m_sand.width(); ++x) {
            if (m_sand.get(x, y) == Sand::SOLID) {
                m_sand.set(x, y, Sand::AIR);
            }
        }
    }

    for (auto& e : m_world) {
        if (!e.body) {
            continue;
        }

        auto rect = e.body->rect;

        for (int y = static_cast<int>(rect.y); y < static_cast<int>(rect.y + rect.h); ++y) {
            for (int x = static_cast<int>(rect.x); x < static_cast<int>(rect.x + rect.w); ++x) {
                m_sand.set(x, y, Sand::SOLID);
            }
        }
    }

    auto mouse_state = input.mouse_state();

    if (mouse_state.buttons) {
        m_sand.set(mouse_state.pos.x - 2, mouse_state.pos.y, Sand::WATER);
        m_sand.set(mouse_state.pos.x - 1, mouse_state.pos.y, Sand::WATER);
        m_sand.set(mouse_state.pos.x, mouse_state.pos.y, Sand::WATER);
        m_sand.set(mouse_state.pos.x + 1, mouse_state.pos.y, Sand::WATER);
        m_sand.set(mouse_state.pos.x + 2, mouse_state.pos.y, Sand::WATER);
    }

    m_sand.simulate(m_world);
}

void Level::render(Renderer& r, float progress_between_frames) {
    r.clear(DARK_GREY);

    m_sand.render(r);
    m_render_system.render(m_world, r, false, progress_between_frames);
}

}  // namespace htn
