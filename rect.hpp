#pragma once

#include "vec2.hpp"

namespace htn {

template <typename T>
struct Rect {
    T x = 0;
    T y = 0;
    T w = 0;
    T h = 0;

    T left() const { return x; }
    T top() const { return y; }
    T right() const { return x + w; }
    T bottom() const { return y + h; }

    Vec2<T> center() const {
        return {x + w / 2, y + h / 2};
    }

    Vec2<T> pos() const { return {x, y}; }

    void set_pos(Vec2<T> p) {
        x = p.x;
        y = p.y;
    }

    Vec2<T> size() const { return {w, h}; }

    void set_size(Vec2<T> s) {
        w = s.x;
        h = s.y;
    }

    Rect<T> moved(Vec2<T> d) const { return {x + d.x, y + d.y, w, h}; }
};

using IntRect = Rect<int>;
using FloatRect = Rect<float>;

}  // namespace htn
