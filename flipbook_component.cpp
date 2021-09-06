#include "flipbook_component.hpp"

namespace htn {

void FlipbookComponent::play(std::shared_ptr<Flipbook> data, bool reset) {
    if (reset && this->data.get() != data.get()) {
        elapsed = 0;
    }

    this->data = std::move(data);
}

}  // namespace htn
