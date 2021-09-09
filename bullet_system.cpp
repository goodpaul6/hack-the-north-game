#include "bullet_system.hpp"

#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void update_bullets(World& world) {
    for (auto& e : world) {
        if (!e.bullet || !e.body) {
            continue;
        }

        float speed = HTN_TWEAK(5);

        if (e.bullet->left) {
            e.body->vel.x = -speed;
        } else {
            e.body->vel.x = speed;
        }
    }
}

}  // namespace htn
