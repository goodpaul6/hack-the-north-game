#include "water_resource_system.hpp"

#include "world.hpp"

namespace htn {

void update_water_resources(World& world) {
    for (auto& e : world) {
        if (!e.water_resource) {
            continue;
        }

        e.water_resource->sim.simulate();
    }
}

}  // namespace htn
