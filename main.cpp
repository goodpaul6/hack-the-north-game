#include "image.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "time.hpp"
#include "window.hpp"

const int WIDTH = 320;
const int HEIGHT = 240;

int main(int argc, char** argv) {
    using namespace htn;

    Window window{"Game", WIDTH, HEIGHT};
    Renderer renderer{window};
    Input input{window};
    Image image{"data/bunny.png"};

    seconds_since_last_call();

    Vec2f image_pos{WIDTH / 2 - image.width() / 2, HEIGHT / 2 - image.height() / 2};

    while (!window.closed()) {
        float seconds_since_last_frame = seconds_since_last_call();

        if (input.key_held(Input::LEFT)) {
            image_pos.x -= 100 * seconds_since_last_frame;
        }

        if (input.key_held(Input::RIGHT)) {
            image_pos.x += 100 * seconds_since_last_frame;
        }

        renderer.clear(DARK_GREY);

        renderer.blit(image, image_pos);

        window.update();
    }

    return 0;
}
