#include "assets.hpp"

namespace htn {

Assets::Assets() {
    player = std::make_shared<Image>("data/bunny.png");
    block = std::make_shared<Image>("data/block.png");
    bullet = std::make_shared<Image>("data/bullet.png");

    player_idle_fb = std::make_shared<Flipbook>();
    player_idle_fb->frames = {{0, 0, 16, 16}};

    player_run_fb = std::make_shared<Flipbook>();
    player_run_fb->frame_time = 0.13f;
    player_run_fb->frames = {{0, 0, 16, 16}, {16, 0, 16, 16}};

    player_jump_fb = std::make_shared<Flipbook>();
    player_jump_fb->frames = {{16, 0, 16, 16}};

    bullet_fb = std::make_shared<Flipbook>();
    bullet_fb->frames = {{0, 0, 16, 16}, {16, 0, 16, 16}};
}

}  // namespace htn
