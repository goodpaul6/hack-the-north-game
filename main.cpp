#include "input.hpp"
#include "level.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "tweaker.hpp"
#include "window.hpp"
#include "logger.hpp"

const int WIDTH = 320;
const int HEIGHT = 180;
const float SIM_TIME = 1 / 60.0f;

int main(int argc, char** argv) {
    using namespace htn;

    Window window{"Game", WIDTH, HEIGHT};
    Renderer renderer{window};
    Input input{window};

    seconds_since_last_call();

    Level level{"data/level.json"};

    float accum_seconds = 0;

    while (!window.closed()) {
        Tweaker::instance().update();

        float dt = seconds_since_last_call();

        level.update(dt);

        accum_seconds += dt;

        // This outer loop could run at any rate

        while (accum_seconds >= SIM_TIME) {
            // This inner loop runs at 60FPS
            level.fixed_update(input, {renderer.width(), renderer.height()});
            accum_seconds -= SIM_TIME;
        }

        level.render(renderer, accum_seconds / SIM_TIME);

        window.update();
    }

    return 0;
}
