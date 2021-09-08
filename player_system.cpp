#include "player_component.hpp"

#include "assets.hpp"
#include "entity_factory.hpp"
#include "input.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_players(World& world, Input& input, Assets& assets) {
    for (auto& e : world) {
        if (!e.player || !e.platformer) {
            continue;
        }

        e.platformer->left = input.key_held('A') || input.key_held(Input::LEFT);
        e.platformer->right = input.key_held('D') || input.key_held(Input::RIGHT);
        e.platformer->jump = input.key_held('W') || input.key_held(Input::UP);

        if (input.key_down('Z') || input.key_down('J')) {
            float middle = e.body->rect.y + e.body->rect.h / 2 - 3 + HTN_TWEAK(2.5);

            if (e.platformer->facing_left) {
                world.add_next_frame(
                    create_bullet(assets, {e.body->rect.x - HTN_TWEAK(12), middle}, true, true));
            } else {
                world.add_next_frame(create_bullet(
                    assets, {e.body->rect.x + e.body->rect.w - HTN_TWEAK(0), middle}, false, true));
            }
        }
    }
}

}  // namespace htn
