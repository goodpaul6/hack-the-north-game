#include "top_down_system.hpp"

#include "world.hpp"

namespace htn {

void update_top_downs(World& world) {
    for (auto& e : world) {
        if (!e.top_down || !e.body) {
            continue;
        }
    }
}

}  // namespace htn
