#include "image.hpp"

#include <stdexcept>
#include <string>
#include <utility>

#include "tigr.h"

namespace htn {

Image::Image(int w, int h) {
    m_data = tigrBitmap(w, h);

    if (!m_data) {
        throw std::runtime_error{"Failed to create empty image"};
    }
}

Image::Image(const char* filename) {
    m_data = tigrLoadImage(filename);

    if (!m_data) {
        throw std::runtime_error{"Failed to load image: " + std::string{filename}};
    }
}

Image::Image(Image&& other) : m_data{std::exchange(other.m_data, nullptr)} {}

Image::~Image() { tigrFree(m_data); }

Image& Image::operator=(Image&& other) {
    m_data = std::exchange(other.m_data, nullptr);
    return *this;
}

int Image::width() const { return m_data->w; }

int Image::height() const { return m_data->h; }

}  // namespace htn
