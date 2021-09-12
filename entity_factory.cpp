#include "entity_factory.hpp"

#include "assets.hpp"
#include "tweaker.hpp"

namespace htn {

Entity create_block(Assets& assets, Vec2f pos) {
    Entity entity;

    ImageComponent image{assets.block};

    BodyComponent body;

    body.affected_by_gravity = false;

    body.rect.set_pos(pos);
    body.rect.set_size({16, 16});

    entity.image = std::move(image);
    entity.body = std::move(body);

    return entity;
}

Entity create_player(Assets& assets, Vec2f pos) {
    Entity entity;

    ImageComponent image{assets.player};

    image.offset.x = -4;

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({8, 16});

    PlatformerComponent platformer;

    platformer.speed = 2;
    platformer.jump_accel = 3;

    platformer.idle_fb = assets.player_idle_fb;
    platformer.run_fb = assets.player_run_fb;
    platformer.jump_fb = assets.player_jump_fb;

    FlipbookComponent flipbook;

    flipbook.data = assets.player_idle_fb;

    HealthComponent health;

    health.hp = 5;
    health.invuln_time = 2;

    PlayerComponent player;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.platformer = std::move(platformer);
    entity.flipbook = std::move(flipbook);
    entity.health = std::move(health);
    entity.player = std::move(player);

    return entity;
}

Entity create_bullet(Assets& assets, Vec2f pos, bool left, bool created_by_player) {
    Entity entity;

    ImageComponent image{assets.bullet};

    image.offset.x = -2;
    image.offset.y = -5;
    image.flip = left;

    FlipbookComponent flipbook;

    flipbook.data = assets.bullet_fb;

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

Entity create_ground_enemy(Assets& assets, Vec2f pos) {
    Entity entity;

    ImageComponent image{assets.ground_enemy};

    image.offset.x = -3;
    image.offset.y = -9;

    FlipbookComponent flipbook;

    flipbook.data = assets.ground_enemy_idle_fb;

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({10, 7});

    PlatformerComponent platformer;

    platformer.speed = 1;
    platformer.idle_fb = assets.ground_enemy_idle_fb;
    platformer.run_fb = assets.ground_enemy_run_fb;
    platformer.jump_fb = assets.ground_enemy_jump_fb;

    GroundMoverComponent ground_mover;

    HealthComponent health;

    health.hp = 1;
    health.invuln_time = 0;

    ParticleEmitterComponent particle_emitter;

    entity.image = std::move(image);
    entity.flipbook = std::move(flipbook);
    entity.body = std::move(body);
    entity.platformer = std::move(platformer);
    entity.ground_mover = std::move(ground_mover);
    entity.health = std::move(health);

    return entity;
}

Entity create_mushroom(Assets& assets, Vec2f pos) {
    ImageComponent image{assets.mushroom};

    BodyComponent body;

    body.rect.set_pos(pos);
    body.rect.set_size({16, 16});

    HealthRegenComponent health_regen;

    health_regen.hp = 1;

    Entity entity;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.health_regen = std::move(health_regen);

    return entity;
}

Entity create_explosion(Vec2f pos) {
    ParticleEmitterComponent particle_emitter;

    particle_emitter.emit_count = static_cast<int>(HTN_TWEAK(20));

    Entity entity;

    entity.fixed_pos = pos;
    entity.particle_emitter = std::move(particle_emitter);

    return entity;
}

}  // namespace htn
