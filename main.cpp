#include "entity.hpp"
#include "image.hpp"
#include "input.hpp"
#include "physics_system.hpp"
#include "platformer_system.hpp"
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
    World world;

    RenderSystem render_system;

    auto player_id = Entity::INVALID_ID;

    {
        Entity player;

        player_id = player.id();

        player.image = {std::make_shared<Image>("data/bunny.png")};
        player.body = {true, true, {0, 0, 16, 16}};
        player.platformer = {false, false};

        Entity block;

        block.image = {std::make_shared<Image>("data/block.png")};
        block.body = {true, false, {0, 100, 100, 16}};

        world.add_next_frame(std::move(player));
        world.add_next_frame(std::move(block));
    }

    seconds_since_last_call();

    float accum_seconds = 0;

    while (!window.closed()) {
        Tweaker::instance().update();

        float seconds_since_last_frame = seconds_since_last_call();

        accum_seconds += seconds_since_last_frame;

        while (accum_seconds >= SIM_TIME) {
            handle_input(world, input);
            simulate_physics(world, {0, 0.1f});

            world.update();

            accum_seconds -= SIM_TIME;
        }

        renderer.clear(DARK_GREY);

        render_system.render(world, renderer, player_id);

        window.update();
    }

    return 0;
}
