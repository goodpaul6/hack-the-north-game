#include <cstdlib>
#include <ctime>

#include "color.hpp"
#include "formatter.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "tweaker.hpp"
#include "water_simulation.hpp"
#include "window.hpp"

const int WIDTH = 320;
const int HEIGHT = 180;
const float SIM_TIME = 1 / 60.0f;

int main(int argc, char** argv) {
    using namespace htn;

    std::srand(std::time(nullptr));

    Window window{"Game", WIDTH, HEIGHT};
    Renderer renderer{window};
    Input input{window};

    seconds_since_last_call();

    float accum_seconds = 0;

    WaterSimulation water_simulation{WIDTH, HEIGHT};

    int mx = 0;
    int my = 0;

    int brush = 1;

    while (!window.closed()) {
        Tweaker::instance().update();

        float dt = seconds_since_last_call();

        accum_seconds += dt;

        if (input.key_down('0')) {
            brush = 0;
        }

        if (input.key_down('1')) {
            brush = 1;
        }

        if (input.key_down('2')) {
            brush = 2;
        }

        if (input.mouse_state(&mx, &my)) {
            water_simulation.set(mx, my, brush);
        }

        while (accum_seconds >= SIM_TIME) {
            water_simulation.fixed_update();
            accum_seconds -= SIM_TIME;
        }

        water_simulation.render(renderer);
        renderer.print(format("Brush: {}", brush).c_str(), {8, 8}, WHITE);

        window.update();
    }

    return 0;
}
