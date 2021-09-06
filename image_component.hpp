#pragma once

#include <memory>

#include "image.hpp"
#include "rect.hpp"

namespace htn {

struct ImageComponent {
    std::shared_ptr<Image> image;
    IntRect src;
    float alpha = 1.0f;
    bool flip = false;

    ImageComponent(std::shared_ptr<Image> image);
};

}  // namespace htn
