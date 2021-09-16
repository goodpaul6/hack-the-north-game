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

Level::Level(const std::string& filename) : m_tilemap{filename} {
    for (auto& object_layer : m_tilemap.object_layers()) {
        if (object_layer.name == "collision") {
            for (auto& object : object_layer.objects) {
                BodyComponent body;

                body.rect = object.rect;
                body.affected_by_gravity = false;

                Entity entity;

                entity.body = std::move(body);

                m_world.add_next_frame(entity);
            }
        } else {
            for (auto& object : object_layer.objects) {
                if (object.type == "player") {
                    auto player = create_player(object.rect.pos());
                    m_player_id = player.id();

                    m_world.add_next_frame(player);
                } else if (object.type == "ground_enemy") {
                    m_world.add_next_frame(create_ground_enemy(object.rect.pos()));
                }
            }
        }
    }
}

void Level::update(float dt) {
    m_world.update();

    update_health(m_world, dt);
    update_flipbooks(m_world, dt);
    update_remove_after_duration(m_world, dt);
}

void Level::fixed_update(Input& input, Vec2f view_size) {
    Vec2f grav_accel{0, HTN_TWEAK(0.1)};

    update_ground_movers(m_world);
    update_players(m_world, input);
    update_platformers(m_world);
    update_bullets(m_world);
    update_bodies(m_world, grav_accel);

    m_render_system.update_camera_offset(m_world, view_size, m_player_id);
}

void Level::render(Renderer& r, float progress_between_frames) {
    r.clear(DARK_GREY);

    m_tilemap.render(r, m_render_system.camera_offset());
    m_render_system.render(m_world, r, HTN_TWEAK(0) > 0, progress_between_frames);
}

}  // namespace htn
