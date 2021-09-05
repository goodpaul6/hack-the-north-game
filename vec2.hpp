#pragma once

#include <cmath>

namespace htn {

template <typename T>
struct Vec2 {
    T x = 0;
    T y = 0;

    Vec2() = default;
    Vec2(T x, T y) : x{x}, y{y} {}

    template <typename U>
    Vec2(U x, U y) : x{static_cast<T>(x)}, y{static_cast<T>(y)} {}

    static Vec2<T> from_angle(float angle, float length = 1.0f) {
        Vec2<T> v{std::cos(angle) * length, std::sin(angle) * length};

        return v;
    }

    float length2() const { return static_cast<float>(x * x + y * y); }

    float length() const { return std::sqrt(length2()); }
};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

template <typename T>
Vec2<T> operator-(const Vec2<T>& a) {
    return Vec2<T>{-a.x, -a.y};
}

template <typename T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>{a.x + b.x, a.y + b.y};
}

template <typename T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>{a.x - b.x, a.y - b.y};
}

template <typename T>
Vec2<T> operator*(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>{a.x * b.x, a.y * b.y};
}

template <typename T>
Vec2<T> operator/(const Vec2<T>& a, const Vec2<T>& b) {
    return Vec2<T>{a.x / b.x, a.y / b.y};
}

template <typename T, typename F>
Vec2<T> operator*(const Vec2<T>& a, F b) {
    return Vec2<T>{a.x * b, a.y * b};
}

template <typename T, typename F>
Vec2<T> operator/(const Vec2<T>& a, F b) {
    return Vec2<T>{a.x / b, a.y / b};
}

template <typename T>
Vec2<T>& operator+=(Vec2<T>& a, const Vec2<T>& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

template <typename T>
Vec2<T>& operator-=(Vec2<T>& a, const Vec2<T>& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template <typename T, typename F>
Vec2<T>& operator*=(Vec2<T>& a, F b) {
    a.x *= b;
    a.y *= b;
    return a;
}

template <typename T, typename F>
Vec2<T>& operator/=(Vec2<T>& a, F b) {
    a.x /= b;
    a.y /= b;
    return a;
}

}  // namespace htn
