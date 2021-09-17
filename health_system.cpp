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

            entity.fixed_pos = e.body->rect.pos();
            entity.particle_emitter = ParticleEmitterComponent{100};
            entity.remove_after_duration = RemoveAfterDurationComponent{HTN_TWEAK(1)};

            world.add_next_frame(entity);
        }

        if (e.health->invuln_time_remaining > 0) {
            e.health->invuln_time_remaining -= dt;
        }
    }
}

}  // namespace htn
