#include "renderer.hpp"

#include <cmath>

#include "image.hpp"
#include "tigr.h"
#include "window.hpp"

namespace htn {

Renderer::Renderer(Window& window) : m_target{window.m_screen} {}

Renderer::Renderer(Image& image) : m_target{image.m_data} {}

void Renderer::clear(Color c) { tigrClear(m_target, c); }

void Renderer::fill(FloatRect rect, Color c) {
    tigrFill(m_target, static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.w),
             static_cast<int>(rect.h), c);
}

void Renderer::rect(FloatRect rect, Color c) {
    tigrRect(m_target, static_cast<int>(rect.x), static_cast<int>(rect.y), static_cast<int>(rect.w),
             static_cast<int>(rect.h), c);
}

void Renderer::line(Vec2f a, Vec2f b, Color c) {
    tigrLine(m_target, static_cast<int>(a.x), static_cast<int>(a.y), static_cast<int>(b.x),
             static_cast<int>(b.y), c);
}

void Renderer::blit(Image& image, Vec2f pos, IntRect src, float alpha, bool flip) {
    if (flip) {
        Image flipped_image_region{src.w, src.h};

        for (int y = 0; y < src.h; ++y) {
            for (int x = 0; x < src.w; ++x) {
                flipped_image_region.m_data->pix[x + y * src.w] =
                    image.m_data->pix[(src.x + src.w - x - 1) + (src.y + y) * image.width()];
            }
        }

        tigrBlitAlpha(m_target, flipped_image_region.m_data, static_cast<int>(pos.x),
                      static_cast<int>(pos.y), 0, 0, src.w, src.h, alpha);
    } else {
        tigrBlitAlpha(m_target, image.m_data, static_cast<int>(pos.x), static_cast<int>(pos.y),
                      src.x, src.y, src.w, src.h, alpha);
    }
}

void Renderer::blit(Image& image, Vec2f pos, float alpha, bool flip) {
    blit(image, pos, {0, 0, image.m_data->w, image.m_data->h}, alpha, flip);
}

int Renderer::width() const { return m_target->w; }
int Renderer::height() const { return m_target->h; }

}  // namespace htn
