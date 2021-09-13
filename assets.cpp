#include "assets.hpp"

namespace htn {

Assets& Assets::instance() {
    static Assets instance;
    return instance;
}

Assets::Assets() {
    block = std::make_shared<Image>("data/block.png");

    player = std::make_shared<Image>("data/bunny.png");

    player_idle_fb = std::make_shared<Flipbook>();
    player_idle_fb->frames = {{0, 0, 16, 16}};

    player_run_fb = std::make_shared<Flipbook>();
    player_run_fb->frame_time = 0.13f;
    player_run_fb->frames = {{0, 0, 16, 16}, {16, 0, 16, 16}};

    player_jump_fb = std::make_shared<Flipbook>();
    player_jump_fb->frames = {{16, 0, 16, 16}};

    bullet = std::make_shared<Image>("data/bullet.png");

    bullet_fb = std::make_shared<Flipbook>();
    bullet_fb->frame_time = 0.001f;
    bullet_fb->loop = false;
    bullet_fb->frames = {{0, 0, 16, 16}, {16, 0, 16, 16}};

    ground_enemy = std::make_shared<Image>("data/ground_enemy.png");

    ground_enemy_idle_fb = std::make_shared<Flipbook>();
    ground_enemy_idle_fb->frames = {{0, 0, 16, 16}};

    ground_enemy_run_fb = std::make_shared<Flipbook>();
    ground_enemy_run_fb->frame_time = 0.13f;
    ground_enemy_run_fb->frames = {{0, 0, 16, 16}, {16, 0, 16, 16}};

    ground_enemy_jump_fb = std::make_shared<Flipbook>();
    ground_enemy_jump_fb->frames = {{0, 0, 16, 16}};
}

}  // namespace htn
