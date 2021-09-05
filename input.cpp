#include "input.hpp"

#include "window.hpp"

namespace htn {

Input::Input(Window& window) : m_screen{window.m_screen} {}

bool Input::key_down(int key) { return tigrKeyDown(m_screen, key); }

bool Input::key_held(int key) { return tigrKeyHeld(m_screen, key); }

}  // namespace htn
