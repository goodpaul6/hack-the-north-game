#include "window.hpp"

#include <stdexcept>

namespace htn {

Window::Window(const char* title, int width, int height) {
    m_screen = tigrWindow(width, height, title, 0);

    if (!m_screen) {
        throw std::runtime_error{"Failed to create window"};
    }
}

Window::~Window() { tigrFree(m_screen); }

bool Window::closed() const { return tigrClosed(m_screen); }

void Window::update() { tigrUpdate(m_screen); }

}  // namespace htn
