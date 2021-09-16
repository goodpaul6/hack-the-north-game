#include "water_simulation.hpp"

#include <cstdlib>
#include <random>

#include "color.hpp"
#include "renderer.hpp"

namespace {

int randint() {
    static std::random_device dev;
    static std::mt19937 rng(dev());
    static std::uniform_int_distribution<std::mt19937::result_type> dist6(-1, 1);

    return dist6(rng);
}

}  // namespace

namespace htn {

WaterSimulation::WaterSimulation(int width, int height)
    : m_width{width}, m_height{height}, m_data(width * height, 0) {}

int WaterSimulation::get(int x, int y) {
    if (x < 0 || x >= m_width) {
        return -1;
    }

    if (y < 0 || y >= m_height) {
        return -1;
    }

    return m_data[x + y * m_width];
}

void WaterSimulation::set(int x, int y, int p) {
    if (x < 0 || x >= m_width) {
        return;
    }

    if (y < 0 || y >= m_height) {
        return;
    }

    m_data[x + y * m_width] = p;
}

void WaterSimulation::fixed_update() {
    for (int y = m_height - 1; y >= 0; --y) {
        for (int x = 0; x < m_width; ++x) {
            auto pix = get(x, y);

            if (get(x, y - 1) == 1 && pix == 0) {
                set(x, y, 1);
                set(x, y - 1, 0);
            }

            if (pix == 1 && get(x, y + 1) == 1) {
                int dx = randint();

                if (get(x + dx, y) == 0) {
                    set(x, y, 0);
                    set(x + dx, y, 1);
                }
            }
        }
    }
}

void WaterSimulation::render(Renderer& r) {
    r.clear(BLACK);

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            if (m_data[x + y * m_width] == 1) {
                r.fill({static_cast<float>(x), static_cast<float>(y), 1, 1}, BLUE);
            } else if (m_data[x + y * m_width] == 2) {
                r.fill({static_cast<float>(x), static_cast<float>(y), 1, 1}, BROWN);
            }
        }
    }
}

}  // namespace htn
