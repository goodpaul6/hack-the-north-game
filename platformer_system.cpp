#include "platformer_system.hpp"

#include "input.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void handle_input(World& world, Input& input) {
    for (auto& e : world) {
        if (!e.platformer || !e.body) {
            continue;
        }

        e.body->vel.x = 0;

        float speed = HTN_TWEAK(2);

        if (input.key_held(Input::LEFT) || input.key_held('A')) {
            e.body->vel.x -= speed;
            e.platformer->facing_left = true;
        }

        if (input.key_held(Input::RIGHT) || input.key_held('D')) {
            e.body->vel.x += speed;
            e.platformer->facing_left = false;
        }

        if (e.platformer->on_ground && (input.key_held(Input::UP) || input.key_held('W'))) {
            e.body->vel.y -= HTN_TWEAK(3);
        }
    }
}

}  // namespace htn
