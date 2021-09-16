#pragma once

#include <vector>

namespace htn {

struct Renderer;

struct WaterSimulation {
    WaterSimulation(int width, int height);

    int get(int x, int y);
    void set(int x, int y, int p);

    void fixed_update();
    void render(Renderer& r);

private:
    int m_width = 0;
    int m_height = 0;
    std::vector<int> m_data;
};

}  // namespace htn
