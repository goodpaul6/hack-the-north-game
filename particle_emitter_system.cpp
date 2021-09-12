#include "particle_emitter_system.hpp"

#include "world.hpp"

namespace htn {

void update_particle_emitters(World& world, Vec2f grav_accel) {
    for (auto& e : world) {
        if (!e.particle_emitter || (!e.body && !e.fixed_pos)) {
            continue;
        }

        Vec2f pos;

        if (e.body) {
            pos = {e.body->rect.x + e.body->rect.w / 2, e.body->rect.y + e.body->rect.h / 2};
        } else {
            pos = *e.fixed_pos;
        }

        e.particle_emitter->manager.emit(pos, e.particle_emitter->emit_count);
        e.particle_emitter->emit_count = 0;

        e.particle_emitter->manager.simulate(grav_accel);
    }
}

}  // namespace htn
