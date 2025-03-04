#pragma once

#include "Components.hpp"

#include <tuple>
#include <string>

class EntityManager;

typedef std::tuple<
	CTransform,
	CLifespan,
	CInput,
	CBoundingBox,
	CAnimation,
	CGravity,
	CState
> ComponentTuple;

class Entity
{
	friend class EntityManager;

    bool              m_active = true;
    const std::string m_tag   = "Default";
    const size_t      m_id    = 0;
	ComponentTuple    m_components;

    Entity(const std::string& tag, size_t id);
public:
    void        queue_free();
    size_t      id() const;
    bool        is_dead() const;
    std::string tag() const;

	template <typename T>
	bool hasComponent() const
	{
		return getComponent<T>().has;
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		auto& component = getComponent<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.has = true;
		return component;
	}

	template<typename T>
	T& getComponent()
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	const T& getComponent() const
	{
		return std::get<T>(m_components);
	}

	template<typename T>
	void removeComponent()
	{
		getComponent<T>() = T();
	}
};