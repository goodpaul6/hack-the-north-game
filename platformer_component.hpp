#pragma once

#include "flipbook.hpp"

namespace htn {

struct PlatformerComponent {
    bool on_ground = false;
    bool facing_left = false;

    std::shared_ptr<Flipbook> idle_fb;
    std::shared_ptr<Flipbook> run_fb;
    std::shared_ptr<Flipbook> jump_fb;
};

}  // namespace htn
