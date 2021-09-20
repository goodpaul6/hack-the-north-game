#include "entity_factory.hpp"
#include "input.hpp"
#include "player_component.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_players(World& world, Input& input, Vec2f camera_offset) {
    for (auto& e : world) {
        if (!e.player || !e.top_down || !e.body) {
            continue;
        }

        e.top_down->left = input.key_held('A') || input.key_held(Input::LEFT);
        e.top_down->right = input.key_held('D') || input.key_held(Input::RIGHT);
        e.top_down->up = input.key_held('W') || input.key_held(Input::UP);
        e.top_down->down = input.key_held('S') || input.key_held(Input::DOWN);

        e.top_down->speed = HTN_TWEAK(1.5);

        auto mouse_state = input.mouse_state();

        if (mouse_state.buttons) {
            Vec2f world_mouse_pos{mouse_state.pos.x, mouse_state.pos.y};

            world_mouse_pos += camera_offset;

            for (auto& w : world) {
                if (!w.water_resource || !w.fixed_pos) {
                    continue;
                }

                auto water_pos = world_mouse_pos - *w.fixed_pos;

                for (int yy = -2; yy < 2; ++yy) {
                    for (int xx = -2; xx < 2; ++xx) {
                        int px = static_cast<int>(water_pos.x + xx);
                        int py = static_cast<int>(water_pos.y + yy);

                        if (px < 0 || px >= w.water_resource->sim.width()) {
                            continue;
                        }

                        if (py < 0 || py >= w.water_resource->sim.height()) {
                            continue;
                        }

                        if (input.key_held(Input::LSHIFT)) {
                            w.water_resource->sim.wall(px, py);
                        } else {
                            w.water_resource->sim.set(px, py,
                                                      w.water_resource->sim.get(px, py) +
                                                          static_cast<int>(HTN_TWEAK(-200)));
                        }
                    }
                }
            }
        }
    }
}

}  // namespace htn
