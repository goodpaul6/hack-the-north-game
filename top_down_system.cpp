#include "top_down_system.hpp"

#include "world.hpp"

namespace htn {

void update_top_downs(World& world) {
    for (auto& e : world) {
        if (!e.top_down || !e.body) {
            continue;
        }

        std::optional<float> angle;

        if (e.top_down->up) {
            angle = -M_PI / 2;

            e.top_down->dir = Direction::UP;

            if (e.top_down->left) {
                *angle -= M_PI / 4;

                e.top_down->dir = Direction::LEFT;
            } else if (e.top_down->right) {
                *angle += M_PI / 4;

                e.top_down->dir = Direction::RIGHT;
            }
        } else if (e.top_down->down) {
            angle = M_PI / 2;

            e.top_down->dir = Direction::DOWN;

            if (e.top_down->left) {
                *angle += M_PI / 4;

                e.top_down->dir = Direction::LEFT;
            } else if (e.top_down->right) {
                *angle -= M_PI / 4;

                e.top_down->dir = Direction::RIGHT;
            }
        } else if (e.top_down->left) {
            angle = M_PI;

            e.top_down->dir = Direction::LEFT;
        } else if (e.top_down->right) {
            angle = 0;

            e.top_down->dir = Direction::RIGHT;
        }

        if (angle) {
            e.body->vel = Vec2f::from_angle(*angle, e.top_down->speed);
        } else {
            e.body->vel = {};
        }

        if (e.flipbook) {
            auto dir = static_cast<size_t>(e.top_down->dir);

            if (angle) {
                e.flipbook->play(e.top_down->walk_fbs[dir], false);
            } else {
                e.flipbook->play(e.top_down->idle_fbs[dir], false);
            }
        }
    }
}

}  // namespace htn
