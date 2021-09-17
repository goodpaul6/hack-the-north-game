#pragma once

#include <vector>

#include "color.hpp"
#include "vec2.hpp"

namespace htn {

struct Renderer;

struct ParticleManager {
    void emit(size_t count, Vec2f pos, Color col);
    void simulate(Vec2f grav_accel);
    void render(Renderer& r, Vec2f camera_offset) const;

private:
    struct Particle {
        Vec2f pos;
        Vec2f vel;
        Color col;
        int frames_remaining = 0;
    };

    std::vector<Particle> m_parts;
};

}  // namespace htn
