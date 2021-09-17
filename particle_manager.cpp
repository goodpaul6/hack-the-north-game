#include "particle_manager.hpp"

#include <algorithm>
#include <random>

#include "renderer.hpp"
#include "tweaker.hpp"

namespace {

float rand_float(float min = 0.0f, float max = 1.0f) {
    std::random_device rd;
    std::mt19937 mt{rd()};
    std::normal_distribution<float> dist{(min + max) / 2.0f, (max - min) / 3.0f};

    return dist(mt);
}

int rand_int(int min, int max) {
    return static_cast<int>(rand_float() * (max - min) + min);
}

}

namespace htn {

void ParticleManager::emit(const EmitParams& params) {
    for (size_t i = 0; i < params.count; ++i) {
        Particle p;

        p.pos = params.pos;
        p.col = params.col;

        p.vel = {rand_float(params.min_x_vel, params.max_x_vel),
                 rand_float(params.min_y_vel, params.max_y_vel)};

        p.frames_remaining = rand_int(params.min_frames_remaining, params.max_frames_remaining);

        m_parts.emplace_back(std::move(p));
    }
}

void ParticleManager::simulate(Vec2f grav_accel) {
    for (auto& p : m_parts) {
        p.pos += p.vel;
        p.vel += grav_accel;
        p.frames_remaining -= 1;
    }

    auto new_end = std::remove_if(m_parts.begin(), m_parts.end(),
                                  [](auto& p) { return p.frames_remaining <= 0; });

    m_parts.erase(new_end, m_parts.end());
}

void ParticleManager::render(Renderer& r, Vec2f camera_offset) const {
    float size = HTN_TWEAK(1);

    for (auto& p : m_parts) {
        r.fill({p.pos.x - camera_offset.x, p.pos.y - camera_offset.y, size, size}, p.col);
    }
}

}  // namespace htn
