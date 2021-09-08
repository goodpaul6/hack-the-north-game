#include "platformer_system.hpp"

#include "input.hpp"
#include "world.hpp"

namespace htn {

void update_platformers(World& world) {
    for (auto& e : world) {
        if (!e.platformer || !e.body || !e.image) {
            continue;
        }

        e.body->vel.x = 0;

        bool move = false;

        if (e.platformer->left) {
            e.body->vel.x -= e.platformer->speed;
            e.platformer->facing_left = true;
            move = true;
        }

        if (e.platformer->right) {
            e.body->vel.x += e.platformer->speed;
            e.platformer->facing_left = false;
            move = true;
        }

        if (!e.platformer->on_ground) {
            e.flipbook->play(e.platformer->jump_fb, false);
        } else if (move) {
            e.flipbook->play(e.platformer->run_fb, false);
        } else {
            e.flipbook->play(e.platformer->idle_fb, false);
        }

        if (e.platformer->on_ground && e.platformer->jump) {
            e.body->vel.y -= e.platformer->jump_accel;
        }

        e.image->flip = e.platformer->facing_left;
    }
}

}  // namespace htn
