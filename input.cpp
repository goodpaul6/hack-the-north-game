#include "input.hpp"

#include "window.hpp"

namespace htn {

Input::Input(Window& window) : m_screen{window.m_screen} {}

bool Input::key_down(int key) { return tigrKeyDown(m_screen, key); }

bool Input::key_held(int key) { return tigrKeyHeld(m_screen, key); }

int Input::mouse_state(int* x, int* y) {
    int buttons = 0;
    tigrMouse(m_screen, x, y, &buttons);

    return buttons;
}

}  // namespace htn
