#include "Scene_Play.hpp"
#include "Physics.hpp"
#include "Assets.hpp"
#include "GameEngine.hpp"
#include "Components.hpp"
#include "Action.hpp"

#include <iostream>

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine)
	, m_levelPath(levelPath)
{
	std::cout << "SCENE CREATED: " << levelPath << std::endl;
	init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath)
{
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE");
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION");

	registerAction(sf::Keyboard::G, "TOGGLE_GRID");

	//Register the rest of the actions here
	registerAction(sf::Keyboard::W, "JUMP");
	registerAction(sf::Keyboard::A, "MOVE_LEFT");
	registerAction(sf::Keyboard::D, "MOVE_RIGHT");
	registerAction(sf::Keyboard::Space, "SHOOT");

	m_gridText.setFont(m_game->assets().getFont("3x6"));
	m_gridText.setCharacterSize(24);
	std::cout << "DEBUG FONT SET: " << m_gridText.getFont() << std::endl;

	loadLevel(levelPath);
}

Vector2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	Vector2 size = entity->getComponent<CAnimation>().animation.getSize() * 0.5f;
	size.y *= -1;
	return Vector2(gridX * m_gridSize.x, height() - gridY * m_gridSize.y) + (size);
}

void Scene_Play::loadLevel(const std::string& filename)
{
	std::cout << "LOADING LEVEL DATA: " << filename << std::endl;
	m_entityManager = EntityManager();

	//read in level file to add all the entities, store player data in m_playerConfig
	std::ifstream fin(filename);
	std::string temp;

	while (fin >> temp)
	{
		if (temp.compare("Deco") == 0)
		{
			std::string anim;
			int x, y;

			fin >> anim >> x >> y;

			auto deco = m_entityManager.addEntity("DECO");
			deco->addComponent<CAnimation>(m_game->assets().getAnimation(anim), true);
			deco->addComponent<CTransform>(gridToMidPixel(x, y, deco));

			std::cout << "\tCREATED DECO: " << anim << ", (" << x << ", " << y << ")" << std::endl;
		}
		else if (temp.compare("Tile") == 0)
		{
			std::string anim;
			int x, y;

			fin >> anim >> x >> y;

			auto tile = m_entityManager.addEntity("TILE");
			tile->addComponent<CAnimation>(m_game->assets().getAnimation(anim), true);
			tile->addComponent<CTransform>(gridToMidPixel(x, y, tile));
			tile->addComponent<CBoundingBox>(m_game->assets().getAnimation(anim).getSize());

			std::cout << "\tCREATED TILE: " << anim << ", (" << x << ", " << y << ")" << std::endl;
		}
		else if (temp.compare("Player") == 0)
		{
			fin >> m_playerConfig.ANIM >> m_playerConfig.X >> m_playerConfig.Y >> m_playerConfig.CX >> m_playerConfig.CY >> m_playerConfig.SPEED;
			fin >> m_playerConfig.JUMP >> m_playerConfig.MAXSPEED >> m_playerConfig.GRAVITY >> m_playerConfig.WEAPON;

			spawnPlayer();

			std::cout << "\tCREATED PLAYER: " << m_playerConfig.ANIM << ", (" << m_playerConfig.X << ", " << m_playerConfig.Y << ")" << std::endl;
			std::cout << "\t\tGRAVITY: " << m_playerConfig.GRAVITY << std::endl;
		}
	}
}

void Scene_Play::spawnPlayer()
{
	m_player = m_entityManager.addEntity("PLAYER");
	m_player->addComponent<CAnimation>(m_game->assets().getAnimation(m_playerConfig.ANIM), true);
	m_player->addComponent<CTransform>(gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player));
	m_player->addComponent<CBoundingBox>(Vector2(m_playerConfig.CX, m_playerConfig.CY));
	m_player->addComponent<CGravity>(m_playerConfig.GRAVITY);

	std::cout << "PLAYER ANIM: " << m_player->getComponent<CAnimation>().animation.getName() << std::endl;
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	// Spawns bullet at the location of the entity, going in the direction the entity is facing
}

void Scene_Play::update()
{
	m_entityManager.update();

	// IMPLEMENT PAUSE FUNCTIONALITY

	sMovement();
	sLifespan();
	sCollision();
	sAnimation();
	sRender();
}

void Scene_Play::sMovement()
{
	//NOTE: setting entity's scale.x to -1 will flip it
	if (m_player->getComponent<CInput>().up and m_player->getComponent<CInput>().canJump)
	{
		m_player->getComponent<CTransform>().velocity.y = m_playerConfig.JUMP;
		m_player->getComponent<CInput>().canJump = false;
	}

	if (m_player->getComponent<CInput>().left)
	{
		m_player->getComponent<CTransform>().velocity.x = -m_playerConfig.SPEED;
	}
	else if (m_player->getComponent<CInput>().right)
	{
		m_player->getComponent<CTransform>().velocity.x = m_playerConfig.SPEED;
	}
	else
	{
		m_player->getComponent<CTransform>().velocity.x = 0;
	}

	for (auto e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CGravity>())
		{
			e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().gravity;
		}

		/*if (e->getComponent<CTransform>().velocity != Vector2(0, 0))
		{
			e->getComponent<CTransform>().velocity.x = std::min(abs(e->getComponent<CTransform>().velocity.x), m_playerConfig.MAXSPEED) * (e->getComponent<CTransform>().velocity.x / abs(e->getComponent<CTransform>().velocity.x));
			e->getComponent<CTransform>().velocity.y = std::min(abs(e->getComponent<CTransform>().velocity.y), m_playerConfig.MAXSPEED) * (e->getComponent<CTransform>().velocity.y / abs(e->getComponent<CTransform>().velocity.y));
		}*/

		e->getComponent<CTransform>().prevPosition = e->getComponent<CTransform>().position;
		e->getComponent<CTransform>().position += e->getComponent<CTransform>().velocity;
	}
}

void Scene_Play::sLifespan()
{
	//Check lifespan of entities that have them, destroy them if lifespan has run out
}

void Scene_Play::sCollision()
{
	// (0, 0) is in the top-left!
	//Implement Physics::GetOverlap() and use it here

	//Implement bullet/tile collisions, destroy tile if it has the brick animation
	//Implement player/tile collisions and resolutions, update player's CState to store on-ground or in-air
	//Check if player has fallen down a hole (y > height())
	//Don't let player walk off the left side of the map
	for (auto e : m_entityManager.getEntities())
	{
		if (e != m_player && Physics().isColliding(e, m_player))
		{
			Vector2 prevOverlap = Physics().GetPreviousOverlap(e, m_player);
			Vector2 overlap = Physics().GetOverlap(e, m_player);
			Vector2 direction = m_player->getComponent<CTransform>().position - m_player->getComponent<CTransform>().prevPosition;

			// Collision from the side
			if (prevOverlap.y > 0 && prevOverlap.x <= 0)
			{
				if (m_player->getComponent<CTransform>().prevPosition.x < e->getComponent<CTransform>().prevPosition.x)
				{
					m_player->getComponent<CTransform>().position.x -= overlap.x;
					m_player->getComponent<CTransform>().velocity.x = 0;
				}
				else
				{
					m_player->getComponent<CTransform>().position.x += overlap.x;
					m_player->getComponent<CTransform>().velocity.x = 0;
				}
			}
			// Collision from top/bottom
			else if (prevOverlap.x > 0 && prevOverlap.y <= 0)
			{
				if (m_player->getComponent<CTransform>().prevPosition.y < e->getComponent<CTransform>().prevPosition.y)
				{
					m_player->getComponent<CTransform>().position.y -= overlap.y;
					m_player->getComponent<CTransform>().velocity.y = 0;

					m_player->getComponent<CInput>().canJump = true;
				}
				else
				{
					m_player->getComponent<CTransform>().position.y += overlap.y;
					m_player->getComponent<CTransform>().velocity.y = 0;
				}
			}
			else
			{
				if (overlap.x > m_playerConfig.SPEED)
				{
					if (m_player->getComponent<CTransform>().prevPosition.y < e->getComponent<CTransform>().prevPosition.y)
					{
						m_player->getComponent<CTransform>().position.y -= overlap.x;
						m_player->getComponent<CTransform>().velocity.y = 0;
					}
					else
					{
						m_player->getComponent<CTransform>().position.y += overlap.x;
						m_player->getComponent<CTransform>().velocity.y = 0;
					}
				}
			}
		}
	}

	if (m_player->getComponent<CTransform>().position.y > height())
	{
		m_player->addComponent<CTransform>(gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, m_player));
	}
}

void Scene_Play::sDoAction(const Action& action)
{
	//std::cout << action.type() << std::endl;
	if (action.type() == "START")
	{
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
		else if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "JUMP") { m_player->getComponent<CInput>().up = true; }
		else if (action.name() == "MOVE_LEFT") { m_player->getComponent<CInput>().left = true; }
		else if (action.name() == "MOVE_RIGHT") { m_player->getComponent<CInput>().right = true; }
		else if (action.name() == "SHOOT") { m_player->getComponent<CInput>().down = true; }
	}
	else if (action.type() == "END")
	{
		if (action.name() == "JUMP") { m_player->getComponent<CInput>().up = false; }
		else if (action.name() == "MOVE_LEFT") { m_player->getComponent<CInput>().left = false; }
		else if (action.name() == "MOVE_RIGHT") { m_player->getComponent<CInput>().right = false; }
		else if (action.name() == "SHOOT") { m_player->getComponent<CInput>().down = false; }
	}
}

void Scene_Play::sAnimation()
{
	// Complete Animation class code
	// Set animation of player based on it's CState component
	/*if (m_player->getComponent<CState>().state == "jumping")
	{
		m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Air"), true);
	}
	if (m_player->getComponent<CState>().state == "run")
	{
		m_player->addComponent<CAnimation>(m_game->assets().getAnimation("Run"), true);
	}*/

	// if anim doesn't repeat and has ended, queue_free() the entity
	for (auto e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CAnimation>())
		{
			e->getComponent<CAnimation>().animation.update();
		}
	}
}

void Scene_Play::onEnd()
{
	// When the scene ends, go back to menu: m_game->changeScene(params);

	//m_game->changeScene("Menu", m_game->getScene("Menu"), true);
}

void Scene_Play::sRender()
{
	// Darken BG if paused
	if (!m_paused) { m_game->window().clear(sf::Color(100, 100, 255)); }
	else { m_game->window().clear(sf::Color(50, 50, 150)); }

	// Center viewport on player if player is far enough right
	auto& pPos = m_player->getComponent<CTransform>().position;
	float windowCenterX = std::max(m_game->window().getSize().x * 0.5f, pPos.x);
	sf::View view = m_game->window().getView();
	view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y);
	m_game->window().setView(view);

	//draw all Entity textures / anims
	if (m_drawTextures)
	{
		for (auto e : m_entityManager.getEntities())
		{
			auto& transform = e->getComponent<CTransform>();

			if (e->hasComponent<CAnimation>())
			{
				auto& animation = e->getComponent<CAnimation>().animation;
				animation.getSprite().setRotation(transform.angle);
				animation.getSprite().setPosition(transform.position.x, transform.position.y);
				animation.getSprite().setScale(transform.scale.x, transform.scale.y);
				m_game->window().draw(animation.getSprite());
			}
		}
	}

	//draw the grid
	if (m_drawGrid)
	{
		float leftX = m_game->window().getView().getCenter().x - width() / 2;
		float rightX = leftX + width() + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);

		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawLine(Vector2(x, 0), Vector2(x, (float)height()));
		}

		for (float y = 0; y < height(); y += m_gridSize.y)
		{
			drawLine(Vector2(leftX, height() - y), Vector2(rightX, height() - y));

			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);

				m_gridText.setString("(" + xCell + ", " + yCell + ")");
				m_gridText.setPosition(x + 3, height() - y - m_gridSize.y + 1);
				m_game->window().draw(m_gridText);
			}
		}
	}

	// draw all Entity bounding boxes
	if (m_drawCollision)
	{
		for (auto e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				auto& box = e->getComponent<CBoundingBox>();
				auto& transform = e->getComponent<CTransform>();
				sf::RectangleShape rect;
				rect.setSize(sf::Vector2f(box.size.x - 1, box.size.y - 1));
				rect.setOrigin(box.halfSize.to_sf_vector());
				rect.setPosition(transform.position.to_sf_vector());
				rect.setFillColor(sf::Color(0, 0, 0, 0));
				rect.setOutlineColor(sf::Color(255, 0, 0, 255));
				rect.setOutlineThickness(1);
				m_game->window().draw(rect);
			}
		}
	}

	m_game->window().display();
}

void Scene_Play::sDebug()
{

}

void Scene_Play::drawLine(const Vector2& p1, const Vector2& p2)
{
	sf::VertexArray line(sf::LineStrip, 2);
	line[0].position = sf::Vector2f(p1.x, p1.y);
	line[0].color = sf::Color::White;
	line[1].position = sf::Vector2f(p2.x, p2.y);
	line[1].color = sf::Color::White;
	m_game->window().draw(line);
}

size_t Scene_Play::width() const
{
	return m_game->window().getSize().x;
}

size_t Scene_Play::height() const
{
	return m_game->window().getSize().y;
}


