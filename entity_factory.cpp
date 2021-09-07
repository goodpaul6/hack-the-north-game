#include "entity_factory.hpp"

#include "assets.hpp"

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

}  // namespace htn
