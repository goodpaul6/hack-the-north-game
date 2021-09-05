#include "entity.hpp"

namespace htn {

Entity::Entity() : m_id{id_counter++} {}

Entity::ID Entity::id() const { return m_id; }

}  // namespace htn
