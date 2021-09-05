#pragma once

#include "color.hpp"

struct Tigr;

namespace htn {

struct Window {
    friend struct Renderer;
    friend struct Input;

    Window(const char* title, int width, int height);
    ~Window();

    bool closed() const;

    void update();

private:
    Tigr* m_screen = nullptr;
};

}  // namespace htn
