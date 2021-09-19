#pragma once

#include <array>
#include <memory>

#include "direction.hpp"
#include "flipbook.hpp"

namespace htn {

struct TopDownComponent {
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;

    float speed = 1;

    Direction dir = Direction::DOWN;

    std::array<std::shared_ptr<Flipbook>, static_cast<size_t>(Direction::COUNT)> idle_fbs;
    std::array<std::shared_ptr<Flipbook>, static_cast<size_t>(Direction::COUNT)> walk_fbs;
};

}  // namespace htn
