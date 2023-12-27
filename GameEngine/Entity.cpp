#include "Entity.hpp"

Entity::Entity(const std::string& tag, size_t id)
    : m_tag(tag)
    , m_id(id)
    , m_alive(true)
{}

std::string Entity::tag() { return m_tag; }
size_t      Entity::id() { return m_id; }
bool        Entity::is_dead() { return !m_alive; }
void        Entity::queue_free() { m_alive = false; }

