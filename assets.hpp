#pragma once

#include <memory>

#include "flipbook.hpp"
#include "image.hpp"

namespace htn {

struct Assets {
    std::shared_ptr<Image> player;

    std::shared_ptr<Flipbook> player_left_fb;
    std::shared_ptr<Flipbook> player_right_fb;
    std::shared_ptr<Flipbook> player_up_fb;
    std::shared_ptr<Flipbook> player_down_fb;

    static Assets& instance();

private:
    Assets();
};

}  // namespace htn

