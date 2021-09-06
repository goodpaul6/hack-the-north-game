#pragma once

struct Tigr;

namespace htn {

struct Image {
    friend struct Renderer;

    Image(int w, int h);
    Image(const char* filename);
    Image(Image&& other);
    Image(const Image& other) = delete;

    ~Image();

    Image& operator=(Image&& other);
    Image& operator=(const Image& other) = delete;

    int width() const;
    int height() const;

private:
    Tigr* m_data = nullptr;
};

}  // namespace htn
