#pragma once

#include <cstdint>
#include <vector>

#include "vec2.hpp"

namespace htn {

struct Renderer;

struct WaterSim {
    WaterSim(int width, int height);

    int get(int x, int y) const;
    void set(int x, int y, int amount);
    void wall(int x, int y);

    void simulate();

    void render(Renderer& r, Vec2f offset);

    int width() const;
    int height() const;

private:
    int m_width = 0;
    int m_height = 0;
    std::vector<int8_t> m_data;
};

}  // namespace htn
