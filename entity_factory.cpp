#include "entity_factory.hpp"

#include "assets.hpp"
#include "tweaker.hpp"

namespace htn {

Entity create_block(Assets& a, Vec2f pos) {
    Entity block;

    block.image = a.block;
    block.body = {true, false, {pos.x, pos.y, 16, 16}};

    return block;
}

Entity create_player(Assets& a, Vec2f pos) {
    Entity player;

    player.image = a.player;
    player.image->offset.x = -4;

    player.body = {true, true, {pos.x, pos.y, 8, 16}};
    player.platformer = {false, false, a.player_idle_fb, a.player_run_fb, a.player_jump_fb};
    player.flipbook = {a.player_idle_fb};

    return player;
}

Entity create_bullet(Assets& a, Vec2f pos, bool left, bool ignore_collision_with_platformer) {
    Entity bullet;

    bullet.image = a.bullet;

    bullet.image->offset.x = -2;

    bullet.image->offset.y = -5;
    bullet.image->flip = left;

    bullet.flipbook = {a.bullet_fb};

    bullet.body = {false, false, {pos.x, pos.y, 12, 6}};
    bullet.bullet = {left, ignore_collision_with_platformer, HTN_TWEAK(1)};

    return bullet;
}

}  // namespace htn
