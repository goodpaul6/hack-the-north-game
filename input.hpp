#pragma once

#include "tigr.h"
#include "vec2.hpp"

namespace htn {

struct Window;

struct Input {
    struct MouseState {
        Vec2i pos;
        int buttons;
    };

    enum { LEFT = TK_LEFT, RIGHT = TK_RIGHT, UP = TK_UP, DOWN = TK_DOWN, LSHIFT = TK_LSHIFT };

    Input(Window& window);

    bool key_down(int key);
    bool key_held(int key);

    MouseState mouse_state();

private:
    Tigr* m_screen = nullptr;
};

}  // namespace htn
