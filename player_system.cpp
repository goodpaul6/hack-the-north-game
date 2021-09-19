#include "entity_factory.hpp"
#include "input.hpp"
#include "player_component.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_players(World& world, Input& input) {
    for (auto& e : world) {
        if (!e.player || !e.top_down || !e.body) {
            continue;
        }

        e.top_down->left = input.key_held('A') || input.key_held(Input::LEFT);
        e.top_down->right = input.key_held('D') || input.key_held(Input::RIGHT);
        e.top_down->up = input.key_held('W') || input.key_held(Input::UP);
        e.top_down->down = input.key_held('S') || input.key_held(Input::DOWN);

        e.top_down->speed = HTN_TWEAK(1.5);
    }
}

}  // namespace htn
