#pragma once

#include <string>

#include "CTransform.hpp"
#include "CShape.hpp"
#include "CCollision.hpp"
//#include "CInput.hpp"
#include "CScore.hpp"
//#include "CLifespan.hpp"

class Entity
{
    const std::string m_tag;
    bool m_alive = true;
    const size_t m_id;

    Entity(const std::string& tag, size_t id);
public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape>     cShape;
    std::shared_ptr<CCollision> cCollision;
    //std::shared_ptr<CInput>     cInput;
    std::shared_ptr<CScore>     cScore;
    //std::shared_ptr<CLifespan>  cLifespan;

    std::string tag();
    size_t id();
    bool is_dead();
    void queue_free();

    friend class EntityManager;
};