#pragma once

#include "Action.hpp"
#include "EntityManager.hpp"

#include <memory>

typedef std::map<int, std::string> ActionMap;

class GameEngine;

class Scene
{
protected:
	GameEngine*      m_game          = nullptr;
	EntityManager    m_entityManager;
	ActionMap        m_actionMap;
	bool             m_paused        = false;
	bool             m_hasEnded      = false;
	size_t           m_currentFrame  = 0;

	virtual void onEnd() = 0;
	void         setPaused(bool paused) { m_paused = paused; }
public:
	Scene(GameEngine* gameEngine) : m_game(gameEngine) {}

	virtual void update() = 0;
	virtual void sDoAction(const Action& action) = 0;
	virtual void sRender() = 0;

	void         simulate(const size_t frames) { for (int i = 0; i < frames; i++) { update(); } }
	void         registerAction(int inputKey, const std::string& actionName) { m_actionMap[inputKey] = actionName; }

	size_t width()        const;
	size_t height()       const;
	size_t currentFrame() const { return m_currentFrame; }

	bool hasEnded()                 const { return m_hasEnded; }
	const ActionMap& getActionMap() const { return m_actionMap; }
	void drawLine(const Vector2& p1, const Vector2& p2);
};
