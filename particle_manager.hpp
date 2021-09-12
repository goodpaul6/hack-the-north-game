#pragma once

#include <vector>

#include "vec2.hpp"

namespace htn {

struct Renderer;

struct ParticleManager {
    void emit(Vec2f pos, size_t number);
    void simulate(Vec2f grav_accel);
    void render(Renderer& renderer, Vec2f camera_offset);

private:
    struct Particle {
        Vec2f pos;
        Vec2f vel;
        size_t frames_remaining = 0;
    };

    std::vector<Particle> m_parts;
};

}  // namespace htn
