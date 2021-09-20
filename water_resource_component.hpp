#pragma once

#include "water_sim.hpp"

namespace htn {

struct WaterResourceComponent {
    WaterSim sim;

    WaterResourceComponent(int width, int height);
};

}  // namespace htn
