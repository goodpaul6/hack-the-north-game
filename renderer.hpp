#pragma once

#include "rect.hpp"
#include "vec2.hpp"

struct Tigr;

namespace htn {

struct Window;
struct Color;
struct Image;

struct Renderer {
    Renderer(Window& window);
    Renderer(Image& image);

    void clear(Color c);

    void fill(FloatRect rect, Color c);

    void rect(FloatRect rect, Color c);

    void line(Vec2f a, Vec2f b, Color c);

    void blit(Image& image, Vec2f pos, IntRect src, float alpha = 1.0f, bool flip = false);
    void blit(Image& image, Vec2f pos, float alpha = 1.0f, bool flip = false);

    int width() const;
    int height() const;

private:
    Tigr* m_target = nullptr;
};

}  // namespace htn
