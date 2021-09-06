#include "flipbook_system.hpp"

#include "flipbook_component.hpp"
#include "world.hpp"

namespace htn {

void update_flipbooks(World& world, float dt) {
    for (auto& e : world) {
        if (!e.flipbook || !e.flipbook->data || !e.image) {
            continue;
        }

        int frame = e.flipbook->data->frame_time > 0
                        ? (static_cast<int>(e.flipbook->elapsed / e.flipbook->data->frame_time) %
                           e.flipbook->data->frames.size())
                        : 0;

        e.image->src = e.flipbook->data->frames[frame];

        e.flipbook->elapsed += dt;
    }
}

}  // namespace htn
