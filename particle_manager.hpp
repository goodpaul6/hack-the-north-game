#pragma once

#include <vector>

#include "color.hpp"
#include "vec2.hpp"
#include "rect.hpp"

namespace htn {

struct Renderer;

struct ParticleManager {
    struct EmitParams {
        size_t count;
        Color col;
        Vec2f pos;

        float min_x_vel = 0;
        float max_x_vel = 0;

        float min_y_vel = 0;
        float max_y_vel = 0;

        int min_frames_remaining = 0;
        int max_frames_remaining = 0;
    };

    void emit(const EmitParams& params);
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
