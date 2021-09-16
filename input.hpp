#pragma once

#include "tigr.h"

namespace htn {

struct Window;

struct Input {
    enum { LEFT = TK_LEFT, RIGHT = TK_RIGHT, UP = TK_UP, DOWN = TK_DOWN };

    Input(Window& window);

    bool key_down(int key);
    bool key_held(int key);

    int mouse_state(int* x, int* y);

private:
    Tigr* m_screen = nullptr;
};

}  // namespace htn
