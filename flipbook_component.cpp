#include "flipbook_component.hpp"

namespace htn {

void FlipbookComponent::play(std::shared_ptr<Flipbook> data) { this->data = std::move(data); }

}  // namespace htn
