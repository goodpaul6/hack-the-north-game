#pragma once

namespace htn {

struct HealthComponent {
    int hp = 1;
    float invuln_time = 0;

    float invuln_time_remaining = 0;

    bool damage(int amount);
};

}  // namespace htn
