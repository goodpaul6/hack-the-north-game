#include "health_component.hpp"

namespace htn {

bool HealthComponent::damage(int amount) {
    if (invuln_time_remaining > 0) {
        return false;
    }

    hp -= amount;
    invuln_time_remaining = invuln_time;

    return true;
}

}  // namespace htn
