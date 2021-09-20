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
#include "top_down_system.hpp"
#include "tweaker.hpp"
#include "water_resource_system.hpp"
#include "world.hpp"

namespace {

// Shamelessly taken from https://stackoverflow.com/a/15599478
bool point_in_polygon(htn::Vec2f point, const std::vector<htn::Vec2f>& points) {
    if (points.empty()) {
        return false;
    }

    bool c = false;

    for (int i = 0, j = points.size() - 1; i < points.size(); j = i++) {
        if (((points[i].y >= point.y) != (points[j].y >= point.y)) &&
            (point.x <=
             (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) +
                 points[i].x)) {
            c = !c;
        }
    }

    return c;
}

}  // namespace

namespace htn {

Level::Level() : m_tilemap{"data/level.json"} {
    for (const auto& object_layer : m_tilemap.object_layers()) {
        if (object_layer.name == "collision") {
            for (const auto& object : object_layer.objects) {
                Entity entity;

                BodyComponent body;

                body.affected_by_gravity = false;
                body.rect = object.rect;

                entity.body = std::move(body);

                m_world.add_next_frame(std::move(entity));
            }
        } else if (object_layer.name == "water_resources") {
            for (const auto& object : object_layer.objects) {
                Entity entity;

                int w = static_cast<int>(object.rect.w);
                int h = static_cast<int>(object.rect.h);

                WaterResourceComponent water_resource{w, h};

                for (int y = 0; y < h; ++y) {
                    for (int x = 0; x < w; ++x) {
                        if (!point_in_polygon({x, y}, object.polygon)) {
                            water_resource.sim.wall(x, y);
                        } else {
                            water_resource.sim.set(x, y, INT8_MAX);
                        }
                    }
                }

                entity.fixed_pos = object.rect.pos();
                entity.water_resource = std::move(water_resource);

                m_world.add_next_frame(std::move(entity));
            }
        } else {
            for (const auto& object : object_layer.objects) {
                if (object.type == "player") {
                    auto player = create_player(object.rect.pos());

                    m_player_id = player.id();

                    m_world.add_next_frame(std::move(player));
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
    update_players(m_world, input, m_render_system.camera_offset());
    update_platformers(m_world);
    update_top_downs(m_world);
    update_bullets(m_world);
    update_bodies(m_world, grav_accel);
    update_particle_emitters(m_world, grav_accel);
    update_water_resources(m_world);

    m_render_system.update_camera_offset(m_world, view_size, m_player_id);
}

void Level::render(Renderer& r, float progress_between_frames) {
    r.clear(DARK_GREY);

    m_tilemap.render(r, m_render_system.camera_offset());
    m_render_system.render(m_world, r, HTN_TWEAK(0) > 0, progress_between_frames);
}

}  // namespace htn
