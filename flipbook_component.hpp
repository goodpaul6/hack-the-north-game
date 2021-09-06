#pragma once

#include <memory>

#include "flipbook.hpp"

namespace htn {

struct FlipbookComponent {
    std::shared_ptr<Flipbook> data;

    float elapsed = 0;

    void play(std::shared_ptr<Flipbook> data);
};

}  // namespace htn
