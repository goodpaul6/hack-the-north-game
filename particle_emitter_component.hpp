#pragma once

#include "particle_manager.hpp"

namespace htn {

struct ParticleEmitterComponent {
    ParticleManager manager;
    size_t emit_count = 0;
};

}  // namespace htn
