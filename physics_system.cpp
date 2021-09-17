#include "physics_system.hpp"

#include <algorithm>

#include "tweaker.hpp"
#include "world.hpp"

namespace htn {

void collide_rect(World& world, FloatRect rect, const Entity* entity_to_ignore,
                  std::vector<Entity*>& collisions) {
    for (auto& e : world) {
        if (&e == entity_to_ignore || !e.alive || !e.body || !e.body->solid) {
            continue;
        }

        if (rect.x + rect.w < e.body->rect.x || e.body->rect.x + e.body->rect.w < rect.x) {
            continue;
        }

        if (rect.y + rect.h < e.body->rect.y || e.body->rect.y + e.body->rect.h < rect.y) {
            continue;
        }

        collisions.emplace_back(&e);
    }
}

Entity* collide_rect(World& world, FloatRect rect, const Entity* entity_to_ignore) {
    std::vector<Entity*> cols;

    collide_rect(world, rect, entity_to_ignore, cols);

    return !cols.empty() ? cols[0] : nullptr;
}

void update_bodies(World& world, Vec2f grav_accel) {
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

        auto new_rect = a.body->rect.moved(a.body->vel);

        if (!collide_rect(world, new_rect, &a)) {
            a.body->rect = new_rect;
            continue;
        }

        new_rect = a.body->rect;

        auto sample_count = a.body->collision_sample_count;

        float dx = a.body->vel.x / sample_count;
        float dy = a.body->vel.y / sample_count;

        const auto handle_collision = [&](auto& b, bool x_axis) {
            if (!x_axis && a.platformer && dy > 0) {
                a.platformer->on_ground = true;
            }

            if (a.bullet) {
                if (a.bullet->created_by_player && b.player) {
                    return false;
                }

                a.alive = false;

                if (b.health && !b.health->damage(1)) {
                    a.alive = true;
                }

                return !a.alive;
            }

            if (a.player && b.bullet && b.bullet->created_by_player) {
                return false;
            }

            if (a.health && b.health_regen) {
                a.health->hp += b.health_regen->amount;
                b.alive = false;
                return false;
            }

            if (x_axis && a.ground_mover && a.platformer) {
                a.platformer->facing_left = !a.platformer->facing_left;
            }

            if (x_axis && a.ground_mover && b.player && b.health) {
                b.health->damage(1);
                return false;
            }

            if (x_axis && a.player && b.ground_mover) {
                return false;
            }

            return true;
        };

        for (int i = 0; i < sample_count; ++i) {
            auto* b = collide_rect(world, new_rect.moved({dx, 0}), &a);

            if (!b || !handle_collision(*b, true)) {
                new_rect.x += dx;
                continue;
            }

            a.body->vel.x = 0;
            break;
        }

        for (int i = 0; i < sample_count; ++i) {
            auto* b = collide_rect(world, new_rect.moved({0, dy}), &a);

            if (!b || !handle_collision(*b, false)) {
                new_rect.y += dy;
                continue;
            }

            a.body->vel.y = 0;
            break;
        }

        a.body->rect = new_rect;
    }
}

}  // namespace htn
