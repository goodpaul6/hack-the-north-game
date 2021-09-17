#include "particle_emitter_system.hpp"

#include "color.hpp"
#include "world.hpp"

namespace htn {

void update_particle_emitters(World& world, Vec2f grav_accel) {
    for (auto& e : world) {
        if (!e.particle_emitter) {
            continue;
        }

        e.particle_emitter->manager.simulate(grav_accel);

        if (e.particle_emitter->emit_params.count > 0) {
            e.particle_emitter->manager.emit(e.particle_emitter->emit_params);
            e.particle_emitter->emit_params.count = 0;
        }
    }
}

}  // namespace htn
