#include "render_system.hpp"

#include "color.hpp"
#include "renderer.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void RenderSystem::update_camera_offset(World& world, Vec2f view_size, Entity::ID camera_focus_id) {
    if (auto* e = world.find(camera_focus_id)) {
        Vec2f offset;

        if (e->fixed_pos) {
            offset = *e->fixed_pos;
        } else if (e->body) {
            offset = {e->body->rect.x + e->body->rect.w / 2, e->body->rect.y + e->body->rect.h / 2};
        }

        offset -= view_size / 2.0f;

        if (m_last_camera_offset) {
            *m_last_camera_offset += (offset - *m_last_camera_offset) * HTN_TWEAK(0.1);
        } else {
            m_last_camera_offset = offset;
        }
    }
}

void RenderSystem::render(World& world, Renderer& r, bool debug_bodies,
                          float progress_between_frames) {
    for (auto& e : world) {
        if (!e.alive) {
            continue;
        }

        if (e.particle_emitter) {
            e.particle_emitter->manager.render(r, camera_offset());
        }

        Vec2f pos;

        if (e.fixed_pos) {
            pos = *e.fixed_pos;
        } else if (e.body) {
            pos = Vec2f{e.body->rect.x, e.body->rect.y} + e.body->vel * progress_between_frames;
        }

        pos -= camera_offset();

        if (debug_bodies && e.body) {
            r.rect({pos.x, pos.y, e.body->rect.w, e.body->rect.h}, RED);
        }

        if (e.image) {
            bool show = true;

            if (e.health && e.health->invuln_time_remaining) {
                int counter = (e.health->invuln_time_remaining / HTN_TWEAK(0.25));
                show = counter % 2 == 0;
            }

            r.blit(*e.image->image, pos + e.image->offset, e.image->src, show ? e.image->alpha : 0,
                   e.image->flip);
        }

        if (e.water_resource) {
            e.water_resource->sim.render(r, pos);
        }
    }
}

Vec2f RenderSystem::camera_offset() const { return m_last_camera_offset.value_or(Vec2f{}); }

}  // namespace htn
