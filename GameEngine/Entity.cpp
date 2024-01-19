#include "Entity.hpp"

Entity::Entity(const std::string& tag, size_t id)
	: m_tag(tag)
	, m_id(id)
	, m_active(true)
{}

std::string Entity::tag() const     { return m_tag; }
size_t      Entity::id() const      { return m_id; }
bool        Entity::is_dead() const { return !m_active; }
void        Entity::queue_free()    { m_active = false; }

