#pragma once

namespace htn {

struct TopDownComponent {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    float speed = 1.0f;
};

}  // namespace htn
