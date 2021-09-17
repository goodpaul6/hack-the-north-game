#include "entity_factory.hpp"

#include "assets.hpp"
#include "tweaker.hpp"

namespace htn {

Entity create_block(Vec2f pos) {
    Entity entity;

    ImageComponent image{Assets::instance().block};

    BodyComponent body;

    body.affected_by_gravity = false;

    body.rect.set_pos(pos);
    body.rect.set_size({16, 16});

    entity.image = std::move(image);
    entity.body = std::move(body);

    return entity;
}

Entity create_player(Vec2f pos) {
    Entity entity;

    ImageComponent image{Assets::instance().player};

    image.offset.x = -4;

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({8, 16});

    PlatformerComponent platformer;

    platformer.speed = 2;
    platformer.jump_accel = 3;

    platformer.idle_fb = Assets::instance().player_idle_fb;
    platformer.run_fb = Assets::instance().player_run_fb;
    platformer.jump_fb = Assets::instance().player_jump_fb;

    FlipbookComponent flipbook;

    flipbook.data = Assets::instance().player_idle_fb;

    PlayerComponent player;

    HealthComponent health;

    health.hp = static_cast<int>(HTN_TWEAK(5));
    health.invuln_time = 2;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.platformer = std::move(platformer);
    entity.flipbook = std::move(flipbook);
    entity.player = std::move(player);
    entity.health = std::move(health);

    return entity;
}

Entity create_bullet(Vec2f pos, bool left, bool created_by_player) {
    Entity entity;

    ImageComponent image{Assets::instance().bullet};

    image.offset.x = -2;
    image.offset.y = -5;
    image.flip = left;

    FlipbookComponent flipbook;

    flipbook.data = Assets::instance().bullet_fb;

    BodyComponent body;

    body.solid = false;
    body.affected_by_gravity = false;

    body.rect.set_pos(pos);
    body.rect.set_size({12, 6});

    BulletComponent bullet;

    bullet.left = left;
    bullet.created_by_player = created_by_player;

    RemoveAfterDurationComponent remove_after_duration;

    remove_after_duration.time_remaining = HTN_TWEAK(1);

    entity.image = std::move(image);
    entity.flipbook = std::move(flipbook);
    entity.body = std::move(body);
    entity.bullet = std::move(bullet);
    entity.remove_after_duration = std::move(remove_after_duration);

    return entity;
}

Entity create_ground_enemy(Vec2f pos) {
    Entity entity;

    ImageComponent image{Assets::instance().ground_enemy};

    image.offset.x = -3;
    image.offset.y = -9;

    FlipbookComponent flipbook;

    flipbook.data = Assets::instance().ground_enemy_idle_fb;

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({10, 7});

    PlatformerComponent platformer;

    platformer.speed = 1;
    platformer.idle_fb = Assets::instance().ground_enemy_idle_fb;
    platformer.run_fb = Assets::instance().ground_enemy_run_fb;
    platformer.jump_fb = Assets::instance().ground_enemy_jump_fb;

    GroundMoverComponent ground_mover;

    HealthComponent health;

    health.hp = 1;
    health.invuln_time = 0;

    entity.image = std::move(image);
    entity.flipbook = std::move(flipbook);
    entity.body = std::move(body);
    entity.platformer = std::move(platformer);
    entity.ground_mover = std::move(ground_mover);
    entity.health = std::move(health);

    return entity;
}

Entity create_mushroom(Vec2f pos) {
    Entity entity;

    ImageComponent image{Assets::instance().mushroom};

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({16, 16});

    HealthRegenComponent health_regen;

    health_regen.amount = 1;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.health_regen = std::move(health_regen);

    return entity;
}

}  // namespace htn
