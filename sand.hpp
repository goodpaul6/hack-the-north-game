#pragma once

#include <cstdint>
#include <vector>

#include "vec2.hpp"

namespace htn {

struct World;
struct Renderer;

struct Sand {
    enum ParticleType : uint8_t {
        AIR,
        SOLID,
        WATER,
    };

    Sand(int width, int height);

    uint8_t get(int x, int y) const;
    void set(int x, int y, uint8_t particle_type);

    void simulate(World& world);
    void render(Renderer& r) const;

    int width() const;
    int height() const;

private:
    int m_width = 0;
    int m_height = 0;

    std::vector<uint8_t> m_data;
};

}  // namespace htn
