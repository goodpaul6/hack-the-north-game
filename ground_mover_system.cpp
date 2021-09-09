#include "ground_mover_system.hpp"

#include "entity.hpp"
#include "physics_system.hpp"
#include "world.hpp"

namespace htn {

void update_ground_movers(World& world) {
    for (auto& e : world) {
        if (!e.ground_mover || !e.platformer || !e.body) {
            continue;
        }

        auto fall_check_x_offset = (e.platformer->facing_left ? -1 : 1) * e.body->rect.w;
        auto fall_check_y_offset = e.body->rect.h;

        if (!collide_rect(world, e.body->rect.moved({fall_check_x_offset, fall_check_y_offset}),
                          &e)) {
            e.platformer->facing_left = !e.platformer->facing_left;
        }

        e.platformer->left = e.platformer->facing_left;
        e.platformer->right = !e.platformer->facing_left;
    }
}

}  // namespace htn

