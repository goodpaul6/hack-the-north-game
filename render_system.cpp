#include "render_system.hpp"

#include "renderer.hpp"
#include "world.hpp"

namespace htn {

void render(World& world, Renderer& r, Entity::ID camera_focus_id) {
    Vec2f camera_offset;

    if (auto* e = world.find(camera_focus_id)) {
        if (e->fixed_pos) {
            camera_offset = *e->fixed_pos;
        } else if (e->body) {
            camera_offset = {e->body->rect.x + e->body->rect.w / 2,
                             e->body->rect.y + e->body->rect.h / 2};
        }

        camera_offset -= Vec2f{r.width() / 2, r.height() / 2};
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

        pos -= camera_offset;

        r.blit(*e.image->image, pos, e.image->src, e.image->alpha);
    }
}

}  // namespace htn
