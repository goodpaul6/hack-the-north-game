#include "particle_manager.hpp"

#include <algorithm>
#include <cstdlib>

#include "renderer.hpp"
#include "tweaker.hpp"

namespace htn {

void ParticleManager::emit(size_t count, Vec2f pos, Color col) {
    float y_speed = HTN_TWEAK(4);
    float x_speed = HTN_TWEAK(2);

    auto frames_remaining = static_cast<int>(HTN_TWEAK(30));

    const auto rand_float = []() { return (static_cast<float>(std::rand()) / RAND_MAX); };

    for (size_t i = 0; i < count; ++i) {
        Particle p;

        p.pos = pos;
        p.col = col;

        p.vel = {(rand_float() - 0.5f) * x_speed, rand_float() * -y_speed};

        p.frames_remaining = static_cast<int>(rand_float() * frames_remaining);

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
    float size = HTN_TWEAK(2);

    for (auto& p : m_parts) {
        r.fill({p.pos.x - camera_offset.x, p.pos.y - camera_offset.y, size, size}, p.col);
    }
}

}  // namespace htn
