#include "entity_factory.hpp"

#include "assets.hpp"
#include "tweaker.hpp"

namespace htn {

Entity create_player(Vec2f pos) {
    Entity entity;

    auto& assets = Assets::instance();

    ImageComponent image{assets.player};

    image.offset = {-5, -3};

    BodyComponent body;

    body.affected_by_gravity = false;

    body.rect.set_pos(pos);
    body.rect.set_size({6, 10});

    TopDownComponent top_down;

    top_down.speed = HTN_TWEAK(5);

    PlayerComponent player;

    entity.image = std::move(image);
    entity.body = std::move(body);
    entity.top_down = std::move(top_down);
    entity.player = std::move(player);

    return entity;
}

}  // namespace htn
