#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Entity.hpp"

typedef std::vector<std::shared_ptr<Entity>>   EntityVector;
typedef std::map   <std::string, EntityVector> EntityMap;
class EntityManager
{
    EntityVector m_entities;
    EntityVector m_toAdd;
    EntityMap    m_entityMap;
    size_t       m_totalEntities = 0;
public:
    EntityManager();

    void update();

    std::shared_ptr<Entity> addEntity(const std::string& tag);
	void removeDeadEntities(EntityVector& vec);

    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
};