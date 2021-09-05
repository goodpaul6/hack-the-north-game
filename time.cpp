#include "time.hpp"

#include "tigr.h"

namespace htn {

float seconds_since_last_call() { return tigrTime(); }

}  // namespace htn
