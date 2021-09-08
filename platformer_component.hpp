#pragma once

#include "flipbook.hpp"

namespace htn {

struct PlatformerComponent {
    float speed = 0;
    float jump_accel = 0;

    bool left = false;
    bool right = false;
    bool jump = false;

    bool on_ground = false;
    bool facing_left = false;

    std::shared_ptr<Flipbook> idle_fb;
    std::shared_ptr<Flipbook> run_fb;
    std::shared_ptr<Flipbook> jump_fb;
};

}  // namespace htn
