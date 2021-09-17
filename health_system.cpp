#include "health_system.hpp"

#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_health(World& world, float dt) {
    for (auto& e : world) {
        if (!e.health) {
            continue;
        }

        e.alive = e.health->hp > 0;

        if (!e.alive && e.body) {
            Entity entity;

            ParticleManager::EmitParams emit_params;

            emit_params.count = static_cast<int>(HTN_TWEAK(30));

            emit_params.pos = e.body->rect.center();
            emit_params.col = RED;

            emit_params.min_x_vel = -1.0f;
            emit_params.max_x_vel = 1.0f;
            emit_params.min_y_vel = -4.0f;
            emit_params.max_y_vel = -2.0f;

            emit_params.min_frames_remaining = 10;
            emit_params.max_frames_remaining = 30;

            entity.particle_emitter = ParticleEmitterComponent{std::move(emit_params)};
            entity.remove_after_duration = RemoveAfterDurationComponent{HTN_TWEAK(1)};

            world.add_next_frame(entity);
        }

        if (e.health->invuln_time_remaining > 0) {
            e.health->invuln_time_remaining -= dt;
        }
    }
}

}  // namespace htn
