#include "platformer_system.hpp"

#include "input.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void handle_input(World& world, Input& input) {
    for (auto& e : world) {
        if (!e.platformer || !e.body || !e.image) {
            continue;
        }

        e.body->vel.x = 0;

        float speed = HTN_TWEAK(2);

        bool move = false;

        if (input.key_held(Input::LEFT) || input.key_held('A')) {
            e.body->vel.x -= speed;
            e.platformer->facing_left = true;
            move = true;
        }

        if (input.key_held(Input::RIGHT) || input.key_held('D')) {
            e.body->vel.x += speed;
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

        if (e.platformer->on_ground && (input.key_held(Input::UP) || input.key_held('W'))) {
            e.body->vel.y -= HTN_TWEAK(3);
        }

        e.image->flip = e.platformer->facing_left;
    }
}

}  // namespace htn
