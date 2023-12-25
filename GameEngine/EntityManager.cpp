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

    EntityVector::iterator pend;
    for (auto& entity : m_entities)
    {
        if (entity->is_dead())
        {
            m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
            m_entityMap[entity->tag()].erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
        }
    }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
    auto entity = std::shared_ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(entity);
    return entity;
}

EntityVector& EntityManager::getEntities()
{
    return m_entities;
}

EntityVector& EntityManager::getEntities(const std::string* tag)
{
    return m_entityMap[*tag];
}
