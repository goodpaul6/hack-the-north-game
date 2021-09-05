#include "world.hpp"

#include <algorithm>

namespace htn {

void World::add_next_frame(Entity e) { m_to_be_added.emplace_back(std::move(e)); }

void World::update() {
    auto removed_start =
        std::remove_if(m_entities.begin(), m_entities.end(), [](auto& e) { return !e.alive; });

    m_entities.erase(removed_start, m_entities.end());

    m_entities.insert(m_entities.begin(), m_to_be_added.begin(), m_to_be_added.end());
    m_to_be_added.clear();
}

Entity* World::find(Entity::ID id) {
    auto found =
        std::find_if(m_entities.begin(), m_entities.end(), [&](auto& e) { return e.id() == id; });

    if (found == m_entities.end()) {
        return nullptr;
    }

    return &(*found);
}

std::vector<Entity>::iterator World::begin() { return m_entities.begin(); }

std::vector<Entity>::iterator World::end() { return m_entities.end(); }

}  // namespace htn
