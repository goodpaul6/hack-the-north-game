#include "flipbook_system.hpp"

#include <algorithm>

#include "flipbook_component.hpp"
#include "world.hpp"

namespace htn {

void update_flipbooks(World& world, float dt) {
    for (auto& e : world) {
        if (!e.flipbook || !e.flipbook->data || !e.image) {
            continue;
        }

        size_t frame = e.flipbook->data->frame_time > 0
                           ? static_cast<size_t>(e.flipbook->elapsed / e.flipbook->data->frame_time)
                           : 0;

        if (e.flipbook->data->loop) {
            frame %= e.flipbook->data->frames.size();
        } else {
            frame = std::min(frame, e.flipbook->data->frames.size() - 1);
        }

        e.image->src = e.flipbook->data->frames[frame];

        e.flipbook->elapsed += dt;
    }
}

}  // namespace htn
