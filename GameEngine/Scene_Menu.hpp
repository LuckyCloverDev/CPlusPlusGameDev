#pragma once

#include "Scene.hpp"
#include <map>
#include <memory>
#include <deque>

#include "EntityManager.hpp"

class Scene_Menu : public Scene
{
protected:
	std::string              m_title;
	std::vector<std::string> m_menuStrings;
	std::vector<std::string> m_levelPaths;
	sf::Text                 m_menuText;
	size_t                   m_selectedMenuIndex = 0;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);
public:
	Scene_Menu(GameEngine* gameEngine = nullptr);

	void sRender();
};