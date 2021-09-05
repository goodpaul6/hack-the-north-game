#pragma once

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
};

using IntRect = Rect<int>;
using FloatRect = Rect<float>;

}  // namespace htn
