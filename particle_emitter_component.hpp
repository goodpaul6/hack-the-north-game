#pragma once

#include "particle_manager.hpp"

namespace htn {

struct ParticleEmitterComponent {
    size_t emit_count = 0;
    ParticleManager manager;
};

}  // namespace htn
