#include "assets.hpp"

namespace htn {

Assets& Assets::instance() {
    static Assets instance;
    return instance;
}

Assets::Assets() {
    player = std::make_shared<Image>("data/player.png");

    player_up_fb = std::make_shared<Flipbook>();

    player_up_fb->frames = {{0, 0, 16, 16}};

    player_down_fb = std::make_shared<Flipbook>();

    player_down_fb->frames = {{16, 0, 16, 16}};

    player_left_fb = std::make_shared<Flipbook>();

    player_left_fb->frames = {{0, 16, 16, 16}};

    player_right_fb = std::make_shared<Flipbook>();

    player_right_fb->frames = {{16, 16, 16, 16}};
}

}  // namespace htn
