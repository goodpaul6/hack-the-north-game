#include "physics_system.hpp"

#include "world.hpp"

namespace htn {

void simulate_physics(World& world, Vec2f grav_accel) {
    const auto collide_rect = [&](auto& me, FloatRect r) -> Entity* {
        for (auto& e : world) {
            if (&e == &me || !e.body || !e.body->solid) {
                continue;
            }

            if (r.x + r.w < e.body->rect.x || e.body->rect.x + e.body->rect.w < r.x) {
                continue;
            }

            if (r.y + r.h < e.body->rect.y || e.body->rect.y + e.body->rect.h < r.y) {
                continue;
            }

            return &e;
        }

        return nullptr;
    };

    for (auto& a : world) {
        if (!a.body) {
            continue;
        }

        if (a.body->affected_by_gravity) {
            a.body->vel += grav_accel;
        }

        if (a.body->vel.x == 0 && a.body->vel.y == 0) {
            continue;
        }

        if (a.platformer) {
            a.platformer->on_ground = false;
        }

        auto new_rect = a.body->rect;

        new_rect.x += a.body->vel.x;

        auto* b = collide_rect(a, new_rect);

        if (b) {
            new_rect.x = a.body->rect.x;
            a.body->vel.x = 0;
        }

        new_rect.y += a.body->vel.y;

        b = collide_rect(a, new_rect);

        if (b) {
            if (a.platformer && a.body->vel.y > 0) {
                a.platformer->on_ground = true;
            }

            new_rect.y = a.body->rect.y;
            a.body->vel.y = 0;
        }

        a.body->rect = new_rect;
    }
}

}  // namespace htn
