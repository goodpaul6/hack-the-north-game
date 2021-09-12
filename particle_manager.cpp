#include "particle_manager.hpp"

#include "color.hpp"
#include "renderer.hpp"
#include "tweaker.hpp"

namespace htn {

void ParticleManager::emit(Vec2f pos, size_t number) {
    float x_vel = HTN_TWEAK(4);
    float y_vel = HTN_TWEAK(4);

    size_t frames_remaining = static_cast<size_t>(HTN_TWEAK(60));

    const auto rand_float = []() { return (static_cast<float>(std::rand()) / RAND_MAX); };

    for (size_t i = 0; i < number; ++i) {
        Particle p;

        p.pos = pos;
        p.vel.x = (rand_float() - 0.5f) * x_vel;
        p.vel.y = -rand_float() * y_vel;
        p.frames_remaining = frames_remaining;

        m_parts.emplace_back(std::move(p));
    }
}

void ParticleManager::simulate(Vec2f grav_accel) {
    for (auto& p : m_parts) {
        p.pos += p.vel;
        p.vel += grav_accel;
        p.frames_remaining -= 1;
    }
}

void ParticleManager::render(Renderer& renderer, Vec2f camera_offset) {
    float size = HTN_TWEAK(2);

    for (auto& p : m_parts) {
        renderer.fill({p.pos.x - size / 2 - camera_offset.x, p.pos.y - size / 2 - camera_offset.y,
                       size, size},
                      RED);
    }
}

}  // namespace htn
