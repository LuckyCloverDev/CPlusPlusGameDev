#pragma once

#include "Scene.hpp"
#include <map>
#include <memory>

#include "EntityManager.hpp"

class Scene_Play : public Scene
{
	struct PlayerConfig
	{
		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string ANIM, WEAPON;
	};
protected:
	std::shared_ptr<Entity> m_player;
	std::string             m_levelPath;
	PlayerConfig            m_playerConfig;
	bool                    m_drawTextures = true;
	bool                    m_drawCollision = false;
	bool                    m_drawGrid = false;
	const Vector2           m_gridSize = { 64, 64 };
	sf::Text                m_gridText;

	void init(const std::string& levelPath);
	void loadLevel(const std::string& filename);

	Vector2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
	size_t width()        const;
	size_t height()       const;

	void sAnimation();
	void sMovement();
	void sLifespan();
	void sCollision();
	void sRender();
	void sDoAction(const Action& action);
	void sDebug();

	void spawnBullet(std::shared_ptr<Entity> entity);
	void spawnPlayer();

	void onEnd();
public:
	Scene_Play(GameEngine* gameEngine, const std::string& levelPath);

	void update();

	void drawLine(const Vector2& p1, const Vector2& p2);
};