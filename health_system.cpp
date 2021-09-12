#include "health_system.hpp"

#include "entity_factory.hpp"
#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_health(World& world, float dt) {
    for (auto& e : world) {
        if (!e.health) {
            continue;
        }

        e.alive = e.health->hp > 0;

        if (!e.alive && e.body) {
            world.add_next_frame(create_explosion(e.body->rect.pos()));
        }

        if (e.health->invuln_time_remaining > 0) {
            e.health->invuln_time_remaining -= dt;
        }
    }
}

}  // namespace htn
