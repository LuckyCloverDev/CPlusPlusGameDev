#include "EntityManager.hpp"


EntityManager::EntityManager() {}

void EntityManager::update()
{
	for (auto entity : m_toAdd)
	{
		m_entities.push_back(entity);
		m_entityMap[entity->tag()].push_back(entity);
	}
	m_toAdd.clear();

	removeDeadEntities(m_entities);
	for (auto& entities : m_entityMap)
	{
		removeDeadEntities(entities.second);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
	m_toAdd.push_back(entity);
	return entity;
}

void EntityManager::removeDeadEntities(EntityVector& vec)
{
	vec.erase(std::remove_if(vec.begin(), vec.end(), [](auto& e) { return e->is_dead(); }), vec.end());
}

EntityVector& EntityManager::getEntities()
{
	return m_entities;
}

EntityVector& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}
