#include "assets.hpp"
#include "bullet_system.hpp"
#include "entity.hpp"
#include "entity_factory.hpp"
#include "flipbook_system.hpp"
#include "ground_mover_system.hpp"
#include "health_system.hpp"
#include "image.hpp"
#include "input.hpp"
#include "physics_system.hpp"
#include "platformer_system.hpp"
#include "player_system.hpp"
#include "remove_after_duration_system.hpp"
#include "render_system.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "tweaker.hpp"
#include "window.hpp"
#include "world.hpp"

const int WIDTH = 320;
const int HEIGHT = 180;
const float SIM_TIME = 1 / 60.0f;

int main(int argc, char** argv) {
    using namespace htn;

    Window window{"Game", WIDTH, HEIGHT};
    Renderer renderer{window};
    Input input{window};
    Assets assets;
    World world;

    RenderSystem render_system;

    auto player_id = Entity::INVALID_ID;

    {
        auto player = create_player(assets, {});

        player_id = player.id();

        world.add_next_frame(std::move(player));

        world.add_next_frame(create_ground_enemy(assets, {50, 50}));

        for (int i = 0; i < 10; ++i) {
            world.add_next_frame(create_block(assets, {160, i * 16}));
            world.add_next_frame(create_block(assets, {i * 16, 100}));
        }
    }

    seconds_since_last_call();

    float accum_seconds = 0;

    while (!window.closed()) {
        Tweaker::instance().update();

        world.update();

        float seconds_since_last_frame = seconds_since_last_call();

        update_flipbooks(world, seconds_since_last_frame);
        update_remove_after_duration(world, seconds_since_last_frame);

        accum_seconds += seconds_since_last_frame;

        while (accum_seconds >= SIM_TIME) {
            update_ground_movers(world);
            update_players(world, input, assets);
            update_platformers(world);
            update_bullets(world);
            update_bodies(world, {0, 0.1f});
            kill_entities_with_zero_health(world);

            accum_seconds -= SIM_TIME;
        }

        renderer.clear(DARK_GREY);

        render_system.render(world, renderer, player_id, HTN_TWEAK(0) > 0);

        window.update();
    }

    return 0;
}
