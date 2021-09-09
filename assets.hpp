#pragma once

#include <memory>

#include "flipbook.hpp"
#include "image.hpp"

namespace htn {

struct Assets {
    std::shared_ptr<Image> block;

    std::shared_ptr<Image> player;
    std::shared_ptr<Flipbook> player_idle_fb;
    std::shared_ptr<Flipbook> player_run_fb;
    std::shared_ptr<Flipbook> player_jump_fb;

    std::shared_ptr<Image> bullet;
    std::shared_ptr<Flipbook> bullet_fb;

    std::shared_ptr<Image> ground_enemy;
    std::shared_ptr<Flipbook> ground_enemy_idle_fb;
    std::shared_ptr<Flipbook> ground_enemy_run_fb;
    std::shared_ptr<Flipbook> ground_enemy_jump_fb;

    Assets();
};

}  // namespace htn

