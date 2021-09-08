#include "platformer_system.hpp"

#include "entity_factory.hpp"
#include "input.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void handle_input(World& world, Input& input, Assets& a) {
    for (auto& e : world) {
        if (!e.platformer || !e.body || !e.image) {
            continue;
        }

        e.body->vel.x = 0;

        float speed = HTN_TWEAK(2);
        float jump = HTN_TWEAK(3);

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
            e.body->vel.y -= jump;
        }

        if (input.key_down('J') || input.key_down('Z')) {
            float middle = e.body->rect.y + e.body->rect.h / 2 - 3 + HTN_TWEAK(2.5);

            if (e.platformer->facing_left) {
                world.add_next_frame(
                    create_bullet(a, {e.body->rect.x - HTN_TWEAK(12), middle}, true, true));
            } else {
                world.add_next_frame(create_bullet(
                    a, {e.body->rect.x + e.body->rect.w - HTN_TWEAK(0), middle}, false, true));
            }
        }

        e.image->flip = e.platformer->facing_left;
    }
}

}  // namespace htn
