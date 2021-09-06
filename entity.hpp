#pragma once

#include <functional>
#include <optional>

#include "body_component.hpp"
#include "flipbook_component.hpp"
#include "image_component.hpp"
#include "platformer_component.hpp"

namespace htn {

struct Entity {
    using ID = std::uint32_t;

    static constexpr ID INVALID_ID = 0;

    bool alive = true;

    std::optional<Vec2f> fixed_pos;
    std::optional<BodyComponent> body;
    std::optional<ImageComponent> image;
    std::optional<FlipbookComponent> flipbook;
    std::optional<PlatformerComponent> platformer;

    Entity();

    ID id() const;

private:
    inline static ID id_counter = 1;

    ID m_id = INVALID_ID;
};

}  // namespace htn
