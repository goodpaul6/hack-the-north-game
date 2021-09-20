#include "water_sim.hpp"

#include <algorithm>

#include "color.hpp"
#include "image.hpp"
#include "renderer.hpp"
#include "tweaker.hpp"

namespace htn {

WaterSim::WaterSim(int width, int height)
    : m_width{width}, m_height{height}, m_data(width * height, 0) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            m_data[x + y * width] = std::rand() % INT8_MAX;
        }
    }
}

int WaterSim::get(int x, int y) const {
    if (x < 0 || x >= m_width) {
        return 0;
    }

    if (y < 0 || y >= m_height) {
        return 0;
    }

    return m_data[x + y * m_width];
}

void WaterSim::set(int x, int y, int amount) {
    if (x < 0 || x >= m_width) {
        return;
    }

    if (y < 0 || y >= m_height) {
        return;
    }

    if (m_data[x + y * m_width] < 0) {
        return;
    }

    m_data[x + y * m_width] = std::max(std::min(amount, INT8_MAX), 0);
}

void WaterSim::wall(int x, int y) {
    if (x < 0 || x >= m_width) {
        return;
    }

    if (y < 0 || y >= m_height) {
        return;
    }

    m_data[x + y * m_width] = -1;
}

void WaterSim::simulate() {
    for (int i = 0; i < 10; ++i) {
        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                auto& v = m_data[x + y * m_width];

                if (v < 0) {
                    continue;
                }

                auto dx = std::rand() % 3 - 1;
                auto dy = std::rand() % 3 - 1;

                if (dx == 0 && dy == 0) {
                    continue;
                }

                if (x + dx < 0 || x + dx >= m_width) {
                    continue;
                }

                if (y + dy < 0 || y + dy >= m_height) {
                    continue;
                }

                auto p = get(x + dx, y + dy);

                if (p < 0) {
                    continue;
                }

                if (p < v) {
                    set(x + dx, y + dy, p + 1);
                    v -= 1;

                    if (v < 0) {
                        v = 0;
                    }
                }
            }
        }
    }
}

void WaterSim::render(Renderer& r, Vec2f offset) {
    Image bg_image{1, 1};
    Image medium_image{1, 1};

    {
        Renderer image_r{bg_image};
        image_r.fill({0, 0, 1, 1}, WATER_BACKGROUND_COLOR);
    }

    {
        Renderer image_r{medium_image};
        image_r.fill({0, 0, 1, 1}, MEDIUM_WATER_BLUE);
    }

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            float v = static_cast<float>(m_data[x + y * m_width]) / INT8_MAX;

            float avg = 0;
            int count = 0;

            for (int yy = -1; yy <= 1; ++yy) {
                for (int xx = -1; xx <= 1; ++xx) {
                    if ((xx == 0 && yy == 0) || (x + xx < 0 || x + xx >= m_width) ||
                        (y + yy < 0 || y + yy >= m_height)) {
                        continue;
                    }

                    avg += static_cast<float>(get(x + xx, y + yy)) / INT8_MAX;
                    count += 1;
                }
            }

            Vec2f pos{static_cast<float>(x) + offset.x, static_cast<float>(y) + offset.y};

            auto translucent_level = HTN_TWEAK(0.2);

            if (v > translucent_level) {
                r.blit(bg_image, pos);
            } else {
                r.blit(bg_image, pos, v / translucent_level);
            }

            avg /= count;

            float dv = std::abs(v - avg);

            if (dv > HTN_TWEAK(0.05)) {
                r.blit(medium_image, pos, v > avg ? 1 : 0.5f);
            } else {
                r.blit(medium_image, pos, v);
            }
        }
    }
}

int WaterSim::width() const { return m_width; }

int WaterSim::height() const { return m_height; }

}  // namespace htn
