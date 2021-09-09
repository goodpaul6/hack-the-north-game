#include "health_system.hpp"

#include "world.hpp"

namespace htn {

void kill_entities_with_zero_health(World& world) {
    for (auto& e : world) {
        if (!e.health) {
            continue;
        }

        e.alive = e.health->hp > 0;
    }
}

}  // namespace htn
