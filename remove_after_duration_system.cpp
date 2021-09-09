#include "remove_after_duration_system.hpp"

#include "world.hpp"

namespace htn {

void update_remove_after_duration(World& world, float dt) {
    for (auto& e : world) {
        if (!e.remove_after_duration) {
            continue;
        }

        if ((e.remove_after_duration->time_remaining -= dt) <= 0) {
            e.alive = false;
        }
    }
}

}  // namespace htn
