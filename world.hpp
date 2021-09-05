#pragma once

#include <optional>
#include <vector>

#include "entity.hpp"

namespace htn {

struct World {
    void add_next_frame(Entity e);
    void update();

    Entity* find(Entity::ID id);

    std::vector<Entity>::iterator begin();
    std::vector<Entity>::iterator end();

private:
    std::vector<Entity> m_entities;
    std::vector<Entity> m_to_be_added;
};

}  // namespace htn
