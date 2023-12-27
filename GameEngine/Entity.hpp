#pragma once

#include <string>

#include "Components.hpp"

class Entity
{
	friend class EntityManager;

    const std::string m_tag   = "Default";
    bool              m_alive = true;
    const size_t      m_id    = 0;

    Entity(const std::string& tag, size_t id);
public:
    std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CFont>      cFont;
    std::shared_ptr<CLifespan>  cLifespan;
    std::shared_ptr<CScore>     cScore;
	std::shared_ptr<CShape>     cShape;
	std::shared_ptr<CText>      cText;
    std::shared_ptr<CTransform> cTransform;

    std::string tag();
    size_t id();
    bool is_dead();
    void queue_free();
};