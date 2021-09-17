#pragma once

#include "particle_manager.hpp"

namespace htn {

struct ParticleEmitterComponent {
    ParticleManager::EmitParams emit_params;
    ParticleManager manager;
};

}  // namespace htn
