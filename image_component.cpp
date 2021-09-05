#include "image_component.hpp"

namespace htn {

ImageComponent::ImageComponent(std::shared_ptr<Image> image)
    : image{std::move(image)}, src{0, 0, this->image->width(), this->image->height()} {}

}  // namespace htn
