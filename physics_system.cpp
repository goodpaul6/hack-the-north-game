#include "physics_system.hpp"

#include <algorithm>

#include "world.hpp"

namespace {

float step(float d) { return std::min(std::abs(d), 0.1f) * (d < 0 ? -1 : 1); }

bool handle_collision(htn::Entity& a, htn::Entity& b, bool x_axis) {
    if (!x_axis && a.platformer && a.body->vel.y > 0) {
        a.platformer->on_ground = true;
    }

    if (a.bullet) {
        if (b.platformer && a.bullet->ignore_collision_with_platformer) {
            return false;
        }

        a.alive = false;
    }

    return true;
}

}  // namespace

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
            for (float d = 0; std::abs(d) < std::abs(a.body->vel.x); d += step(a.body->vel.x)) {
                float prev_x = new_rect.x;
                new_rect.x = a.body->rect.x + d;

                if (b = collide_rect(a, new_rect)) {
                    new_rect.x = prev_x;
                    break;
                }
            }

            if (handle_collision(a, *b, true)) {
                a.body->vel.x = 0;
            }
        }

        new_rect.y += a.body->vel.y;

        b = collide_rect(a, new_rect);

        if (b) {
            for (float d = 0; std::abs(d) < std::abs(a.body->vel.y); d += step(a.body->vel.y)) {
                float prev_y = new_rect.y;
                new_rect.y = a.body->rect.y + d;

                if (b = collide_rect(a, new_rect)) {
                    new_rect.y = prev_y;
                    break;
                }
            }

            if (handle_collision(a, *b, false)) {
                a.body->vel.y = 0;
            }
        }

        a.body->rect = new_rect;
    }
}

}  // namespace htn
