#pragma once

#include "EntityManager.hpp"

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	std::shared_ptr<Entity> m_player;
	bool m_paused = false;
	bool m_running = true;
public:
	Game();
	void process();

	void sMovement();
	void sUserInput();
	void sRender();
	void sEnemySpawner();
	void sCollision();
};