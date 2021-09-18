#include "sand.hpp"

#include <cstdlib>

#include "color.hpp"
#include "renderer.hpp"

namespace htn {

Sand::Sand(int width, int height) : m_width{width}, m_height{height}, m_data(width * height, 0) {}

uint8_t Sand::get(int x, int y) const {
    if (x < 0 || x >= m_width) {
        return AIR;
    }

    if (y < 0 || y >= m_height) {
        return AIR;
    }

    return m_data[x + y * m_width];
}

void Sand::set(int x, int y, uint8_t particle_type) {
    if (x < 0 || x >= m_width) {
        return;
    }

    if (y < 0 || y >= m_height) {
        return;
    }

    m_data[x + y * m_width] = particle_type;
}

void Sand::simulate(World& world) {
    for (int y = m_height; y >= 0; --y) {
        for (int x = 0; x < m_width; ++x) {
            auto p = m_data[x + y * m_width];

            if (p == WATER) {
                auto b = get(x, y + 1);

                if (b == AIR) {
                    set(x, y + 1, p);
                    set(x, y, AIR);
                } else {
                    int dx = std::rand() < RAND_MAX / 2 ? -1 : 1;

                    if (get(x + dx, y) == AIR) {
                        set(x + dx, y, p);
                        set(x, y, AIR);
                    }
                }
            }
        }
    }
}

void Sand::render(Renderer& r) const {
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            auto p = m_data[x + y * m_width];

            if (p == WATER) {
                r.fill({static_cast<float>(x), static_cast<float>(y), 1, 1}, BLUE);
            }
        }
    }
}

int Sand::width() const { return m_width; }

int Sand::height() const { return m_height; }

}  // namespace htn
