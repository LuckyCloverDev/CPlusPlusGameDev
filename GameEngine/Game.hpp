#pragma once

#include "EntityManager.hpp"
#include "Input.hpp"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, ORMIN, OGMIN, OBMIN, ORMAX, OGMAX, OBMAX, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;

	sf::Font m_font;
	sf::Text m_text;
	std::shared_ptr<Entity> m_player;

	sf::Clock m_clock;
	Input m_input = Input();
	float m_delta = 0.0166f;

	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;

	bool m_paused = false;
	bool m_running = true;

	void process();

	void sMovement();
	void sUserInput();
	void sLifespan();
	void sRender();
	void sEnemySpawner();
	void sCollision();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemy(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

	bool is_running();
	Vector2 get_global_mouse_position();
	int randi_range(int min, int max);
	bool is_colliding(const Entity& e1, const Entity& e2);
public:
	Game();

	void run();
};