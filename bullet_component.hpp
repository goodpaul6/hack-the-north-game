#pragma once

namespace htn {

struct BulletComponent {
    bool left = false;
    bool ignore_collision_with_platformer = false;
    float time_remaining = 2;
};

}  // namespace htn
