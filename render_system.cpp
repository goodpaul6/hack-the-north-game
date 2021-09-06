#include "render_system.hpp"

#include "renderer.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void RenderSystem::render(World& world, Renderer& r, Entity::ID camera_focus_id) {
    if (auto* e = world.find(camera_focus_id)) {
        Vec2f offset;

        if (e->fixed_pos) {
            offset = *e->fixed_pos;
        } else if (e->body) {
            offset = {e->body->rect.x + e->body->rect.w / 2, e->body->rect.y + e->body->rect.h / 2};
        }

        offset -= Vec2f{r.width() / 2, r.height() / 2};

        if (m_last_camera_offset) {
            *m_last_camera_offset += (offset - *m_last_camera_offset) * HTN_TWEAK_FLOAT(0.1);
        } else {
            m_last_camera_offset = offset;
        }
    }

    for (auto& e : world) {
        if (!e.image) {
            continue;
        }

        Vec2f pos;

        if (e.fixed_pos) {
            pos = *e.fixed_pos;
        } else if (e.body) {
            pos = {e.body->rect.x, e.body->rect.y};
        }

        pos -= m_last_camera_offset.value_or(Vec2f{});

        r.blit(*e.image->image, pos, e.image->src, e.image->alpha);
    }
}

}  // namespace htn
