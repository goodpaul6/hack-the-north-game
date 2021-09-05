#pragma once

struct Tigr;

namespace htn {

struct Image {
    friend struct Renderer;

    Image(int w, int h);
    Image(const char* filename);

    ~Image();

    int width() const;
    int height() const;

private:
    Tigr* m_data = nullptr;
};

}  // namespace htn
