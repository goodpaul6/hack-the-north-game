#include "entity_factory.hpp"

#include "assets.hpp"
#include "tweaker.hpp"

namespace htn {

Entity create_player(Vec2f pos) {
    Entity entity;

    auto& assets = Assets::instance();

    ImageComponent image{assets.player};

    image.offset = {-4, -4};

    BodyComponent body;

    body.affected_by_gravity = false;

    body.rect.set_pos(pos);
    body.rect.set_size({8, 10});

    FlipbookComponent flipbook;

    flipbook.data = Assets::instance().player_down_fb;

    TopDownComponent top_down;

    top_down.idle_fbs = {{assets.player_left_fb, assets.player_right_fb, assets.player_up_fb,
                          assets.player_down_fb}};

    top_down.walk_fbs = {{assets.player_left_fb, assets.player_right_fb, assets.player_up_fb,
                          assets.player_down_fb}};

    top_down.speed = HTN_TWEAK(5);

    PlayerComponent player;

    HealthComponent health;

    health.hp = static_cast<int>(HTN_TWEAK(5));
    health.invuln_time = 2;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.top_down = std::move(top_down);
    entity.flipbook = std::move(flipbook);
    entity.player = std::move(player);
    entity.health = std::move(health);

    return entity;
}

}  // namespace htn
