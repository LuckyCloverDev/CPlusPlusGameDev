#include "Game.hpp"
#include <fstream>

Game::Game()
{
	int WINDOW_WIDTH = 640;
	int WINDOW_HEIGHT = 480;
	int FRAME_LIMIT = 60;
	bool FULLSCREEN = false;

	std::ifstream fin("config.txt");
	std::string temp;

	unsigned int font_size;

	float bg_offset = 0.f;
	for (int i = -2; i <= 32; i++)
	{
		for (int j = -2; j <= 18; j++)
		{
			if ((abs(i) % 2 == 0 && abs(j) % 2 == 0) || (abs(i) % 2 == 1 && abs(j) % 2 == 1))
			{
				continue;
			}
			unsigned int rect_col = 20 - (int)(10.f * sqrtf(abs(i - 16) / 16.f));

			std::shared_ptr<Entity> entity = m_entities.addEntity("Background");
			entity->cTransform = std::make_shared<CTransform>();
			entity->cShape = std::make_shared<CShape>(40.f, 40.f, sf::Color(rect_col, rect_col, rect_col));
			entity->cShape->rectShape.setPosition(sf::Vector2f(i * 40.f, j * 40.f));
		}
	}

	while (fin >> temp)
	{
		if (temp.compare("Window") == 0)
		{
			fin >> WINDOW_WIDTH >> WINDOW_HEIGHT >> FRAME_LIMIT >> FULLSCREEN;

			if (FULLSCREEN)
			{
				m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Wars", sf::Style::Fullscreen);
			}
			else
			{
				m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Geometry Wars");
			}
			m_window.setVerticalSyncEnabled(true);
			m_window.setFramerateLimit(FRAME_LIMIT);
		}
		else if (temp.compare("Font") == 0)
		{
			std::string font_file;
			int r, g, b;

			fin >> font_file >> font_size >> r >> g >> b;

			m_font.loadFromFile(font_file);

			m_text.setFont(m_font);
			m_text.setCharacterSize(font_size);
			m_text.setFillColor(sf::Color(r, g, b));
			m_text.setString(sf::String("Score: 0"));
			m_text.setPosition(sf::Vector2f(10, 0));
		}
		else if (temp.compare("Player") == 0)
		{
			fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB;
			fin >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;

			spawnPlayer();
		}
		else if (temp.compare("Enemy") == 0)
		{
			fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.ORMIN >> m_enemyConfig.OGMIN >> m_enemyConfig.OBMIN >> m_enemyConfig.ORMAX;
			fin >> m_enemyConfig.OGMAX >> m_enemyConfig.OBMAX >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
		}
		else if (temp.compare("Bullet") == 0)
		{
			// Shape radius > col radius > speed > fill color > outline color > outline thickness > num vertices > lifespan
			fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB;
			fin >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
		}
	}
}

void Game::run()
{
	while (is_running())
	{
		float fps = 1.f / m_delta;

		//printf("%d Entities\t\t\t\t\t>> %.2f\n", m_entities.getEntities().size(), fps);

		process();
	}
}

void Game::process()
{
	m_delta = m_clock.restart().asSeconds();
	m_entities.update();

	sUserInput();

	if (m_input.is_action_just_pressed(BUTTON_P))
	{
		m_paused = !m_paused;
	}

	if (!m_paused)
	{
		sEnemySpawner();
		sLifespan();
		sMovement();
		sCollision();
	}
	sRender();
	m_currentFrame++;
}

void Game::sMovement()
{
	m_player->cTransform->position += Vector2((float)m_input.get_axis(BUTTON_A, BUTTON_D), (float)m_input.get_axis(BUTTON_W, BUTTON_S)).normalized() * 320.f * m_delta;
	m_player->cShape->circleShape.setPosition(m_player->cTransform->position.to_sf_vector());

	for (auto& entity : m_entities.getEntities("Enemy"))
	{
		entity->cTransform->position += entity->cTransform->velocity;
		entity->cShape->circleShape.setPosition(entity->cTransform->position.to_sf_vector());
	}
	for (auto& entity : m_entities.getEntities("SmallEnemy"))
	{
		entity->cTransform->position += entity->cTransform->velocity;
		entity->cShape->circleShape.setPosition(entity->cTransform->position.to_sf_vector());
	}
	for (auto& entity : m_entities.getEntities("Bullet"))
	{
		entity->cTransform->position += entity->cTransform->velocity;
		entity->cShape->circleShape.setPosition(entity->cTransform->position.to_sf_vector());
	}
}

void Game::sUserInput()
{

	for (int i = 0; i < BUTTON_COUNT; i++)
	{

		m_input.buttons[i].changed = false;
	}

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
				m_running = false;
			} break;

			case sf::Event::MouseButtonReleased:
			case sf::Event::MouseButtonPressed:
			{
				switch (event.key.code)
				{
					process_mouse_button(MOUSE_LEFT, sf::Mouse::Left);
					process_mouse_button(MOUSE_RIGHT, sf::Mouse::Right);
				}
			} break;

			case sf::Event::KeyReleased:
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
					process_button(BUTTON_W, sf::Keyboard::W);
					process_button(BUTTON_A, sf::Keyboard::A);
					process_button(BUTTON_S, sf::Keyboard::S);
					process_button(BUTTON_D, sf::Keyboard::D);

					process_button(BUTTON_P, sf::Keyboard::P);
				}
			} break;
		}
	}

	if (m_input.is_action_just_pressed(MOUSE_LEFT))
	{
		printf("ATTEMPTING??\n");
		spawnBullet(m_player);
	}
}

void Game::sLifespan()
{
	for (auto& entity : m_entities.getEntities("SmallEnemy"))
	{
		entity->cLifespan->remaining -= 1;
		entity->cShape->circleShape.setOutlineColor(sf::Color(entity->cShape->circleShape.getOutlineColor().r, entity->cShape->circleShape.getOutlineColor().g, entity->cShape->circleShape.getOutlineColor().b, (int)(255.f * entity->cLifespan->remaining / entity->cLifespan->total)));
		entity->cShape->circleShape.setFillColor(sf::Color(20, 20, 20, (int)(255.f * entity->cLifespan->remaining / entity->cLifespan->total)));
		if (entity->cLifespan->remaining == 0)
		{
			entity->queue_free();
		}
	}
	for (auto& entity : m_entities.getEntities("Bullet"))
	{
		entity->cLifespan->remaining -= 1;
		entity->cShape->circleShape.setOutlineColor(sf::Color(entity->cShape->circleShape.getOutlineColor().r, entity->cShape->circleShape.getOutlineColor().g, entity->cShape->circleShape.getOutlineColor().b, (int)(255.f * entity->cLifespan->remaining / entity->cLifespan->total)));
		entity->cShape->circleShape.setFillColor(sf::Color(255, 255, 255, (int)(255.f * entity->cLifespan->remaining / entity->cLifespan->total)));
		if (entity->cLifespan->remaining == 0)
		{
			entity->queue_free();
		}
	}
}

void Game::sRender()
{
	m_window.clear();

	for (auto& entity : m_entities.getEntities("Background"))
	{
		entity->cShape->rectShape.move(sf::Vector2f(40 * m_delta, 40 * m_delta));
		//entity->cShape->rectShape->rotate(m_delta * 240.f);
		entity->cTransform->offset += Vector2(40 * m_delta, 40 * m_delta);

		if (entity->cTransform->offset.x >= 40.f)
		{
			entity->cShape->rectShape.move((entity->cTransform->offset * -1).to_sf_vector());
			entity->cTransform->offset *= 0.f;
		}

		m_window.draw(entity->cShape->rectShape);
	}

	for (auto& enemy : m_entities.getEntities("Enemy"))
	{
		enemy->cTransform->angle += m_delta * 180.f;
		enemy->cShape->circleShape.setRotation(enemy->cTransform->angle);
		m_window.draw(enemy->cShape->circleShape);
	}

	for (auto& enemy : m_entities.getEntities("SmallEnemy"))
	{
		enemy->cTransform->angle += m_delta * 180.f;
		enemy->cShape->circleShape.setRotation(enemy->cTransform->angle);
		m_window.draw(enemy->cShape->circleShape);
	}

	for (auto& bullet : m_entities.getEntities("Bullet"))
	{
		bullet->cTransform->angle += m_delta * 180.f;
		bullet->cShape->circleShape.setRotation(bullet->cTransform->angle);
		m_window.draw(bullet->cShape->circleShape);
	}

	m_player->cTransform->angle += m_delta * 180.f;
	m_player->cShape->circleShape.setRotation(m_player->cTransform->angle);
	m_window.draw(m_player->cShape->circleShape);

	m_text.setString("Score: " + std::to_string(m_score));
	m_window.draw(m_text);

	if (m_paused)
	{
		std::shared_ptr<sf::RectangleShape> overlay = std::make_shared<sf::RectangleShape>((sf::Vector2f)m_window.getSize());
		overlay->setFillColor(sf::Color(0, 0, 0, 150));
		m_window.draw(*overlay);

	}

	m_window.display();
}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
	{
		m_lastEnemySpawnTime = m_currentFrame;
		spawnEnemy();
	}
}

void Game::sCollision()
{
	if (m_player->cTransform->position.distance_to_squared(Vector2(m_player->cTransform->position.x, 0)) < (m_player->cCollision->radius * m_player->cCollision->radius))
	{
		m_player->cTransform->position.y = m_player->cCollision->radius;
	}
	else if (m_player->cTransform->position.distance_to_squared(Vector2(m_player->cTransform->position.x, (float)m_window.getSize().y)) < (m_player->cCollision->radius * m_player->cCollision->radius))
	{
		m_player->cTransform->position.y = m_window.getSize().y - m_player->cCollision->radius;
	}

	if (m_player->cTransform->position.distance_to_squared(Vector2(0, m_player->cTransform->position.y)) < (m_player->cCollision->radius * m_player->cCollision->radius))
	{
		m_player->cTransform->position.x = m_player->cCollision->radius;
	}
	else if (m_player->cTransform->position.distance_to_squared(Vector2((float)m_window.getSize().x, m_player->cTransform->position.y)) < (m_player->cCollision->radius * m_player->cCollision->radius))
	{
		m_player->cTransform->position.x = m_window.getSize().x - m_player->cCollision->radius;
	}

	for (auto& entity : m_entities.getEntities("Enemy"))
	{
		if (is_colliding(*entity, *m_player))
		{
			m_player->cTransform->position = Vector2(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
			m_score -= entity->cScore->score;
			spawnSmallEnemy(entity);
			entity->queue_free();
		}

		for (auto& bullet : m_entities.getEntities("Bullet"))
		{
			if (is_colliding(*entity, *bullet))
			{
				m_score += entity->cScore->score;
				spawnSmallEnemy(entity);
				bullet->queue_free();
				entity->queue_free();
			}
		}

		if (entity->cTransform->position.distance_to_squared(Vector2(entity->cTransform->position.x, 0)) < (entity->cCollision->radius * entity->cCollision->radius))
		{
			entity->cTransform->position.y = entity->cCollision->radius;
			entity->cTransform->velocity.y *= -1;
		}
		else if (entity->cTransform->position.distance_to_squared(Vector2(entity->cTransform->position.x, (float)m_window.getSize().y)) < (entity->cCollision->radius * entity->cCollision->radius))
		{
			entity->cTransform->position.y = m_window.getSize().y - entity->cCollision->radius;
			entity->cTransform->velocity.y *= -1;
		}

		if (entity->cTransform->position.distance_to_squared(Vector2(0, entity->cTransform->position.y)) < (entity->cCollision->radius * entity->cCollision->radius))
		{
			entity->cTransform->position.x = entity->cCollision->radius;
			entity->cTransform->velocity.x *= -1;
		}
		else if (entity->cTransform->position.distance_to_squared(Vector2((float)m_window.getSize().x, entity->cTransform->position.y)) < (entity->cCollision->radius * entity->cCollision->radius))
		{
			entity->cTransform->position.x = m_window.getSize().x - entity->cCollision->radius;
			entity->cTransform->velocity.x *= -1;
		}
	}

	for (auto& entity : m_entities.getEntities("SmallEnemy"))
	{
		if (is_colliding(*entity, *m_player))
		{
			m_player->cTransform->position = Vector2(m_window.getSize().x * 0.5f, m_window.getSize().y * 0.5f);
			m_score -= entity->cScore->score;
			entity->queue_free();
		}

		for (auto& bullet : m_entities.getEntities("Bullet"))
		{
			if (is_colliding(*entity, *bullet))
			{
				m_score += entity->cScore->score;
				bullet->queue_free();
				entity->queue_free();
			}
		}
	}
}

void Game::spawnPlayer()
{
	m_player = m_entities.addEntity("Player");
	m_player->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);
	m_player->cTransform = std::make_shared<CTransform>();
	m_player->cTransform->position = Vector2(m_window.getSize().x / 2.f, m_window.getSize().y / 2.f);
	m_player->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);
	m_player->cShape->circleShape.setPosition(m_player->cTransform->position.to_sf_vector());
}

void Game::spawnEnemy()
{
	int vertices = randi_range(m_enemyConfig.VMIN, m_enemyConfig.VMAX);

	std::shared_ptr<Entity> enemy = m_entities.addEntity("Enemy");
	enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);
	enemy->cTransform = std::make_shared<CTransform>();
	enemy->cTransform->position = Vector2((float)(randi_range(m_enemyConfig.CR, m_window.getSize().x - m_enemyConfig.CR)), (float)(randi_range(m_enemyConfig.CR, m_window.getSize().y - m_enemyConfig.CR)));
	enemy->cTransform->velocity = Vector2((float)randi_range(m_enemyConfig.SMIN, m_enemyConfig.SMAX), (float)randi_range(m_enemyConfig.SMIN, m_enemyConfig.SMAX));
	enemy->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(20, 20, 20),
		sf::Color(randi_range(m_enemyConfig.ORMIN, m_enemyConfig.ORMAX), randi_range(m_enemyConfig.OGMIN, m_enemyConfig.OGMAX), randi_range(m_enemyConfig.OBMIN, m_enemyConfig.OBMAX)), m_enemyConfig.OT);
	enemy->cShape->circleShape.setPosition(m_player->cTransform->position.to_sf_vector());
	enemy->cScore = std::make_shared<CScore>(vertices * 100);
}

void Game::spawnSmallEnemy(std::shared_ptr<Entity> entity)
{
	for (int i = 0; i < entity->cShape->circleShape.getPointCount(); i++)
	{
		std::shared_ptr<Entity> sEnemy = m_entities.addEntity("SmallEnemy");
		sEnemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR * 0.5f);
		sEnemy->cTransform = std::make_shared<CTransform>();
		sEnemy->cTransform->position = Vector2(entity->cTransform->position);
		sEnemy->cTransform->velocity = entity->cTransform->velocity.rotate(360.f / entity->cShape->circleShape.getPointCount() * i, false) * 0.5f;
		sEnemy->cShape = std::make_shared<CShape>(m_enemyConfig.SR * 0.5f, entity->cShape->circleShape.getPointCount(), sf::Color(20.f, 20.f, 20.f),
			entity->cShape->circleShape.getOutlineColor(), m_enemyConfig.OT);
		sEnemy->cShape->circleShape.setPosition(entity->cTransform->position.to_sf_vector());
		sEnemy->cScore = std::make_shared<CScore>(entity->cScore->score * 2);
		sEnemy->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity)
{
	std::shared_ptr<Entity> bullet = m_entities.addEntity("Bullet");
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);
	bullet->cTransform = std::make_shared<CTransform>();
	bullet->cTransform->position = Vector2(entity->cTransform->position);
	bullet->cTransform->velocity = (get_global_mouse_position() - bullet->cTransform->position).normalized() * m_bulletConfig.S;
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
		sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);
	bullet->cShape->circleShape.setPosition(bullet->cTransform->position.to_sf_vector());
	bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
}

bool Game::is_running()
{
	return m_running;
}

Vector2 Game::get_global_mouse_position()
{
	return Vector2((float)sf::Mouse::getPosition(m_window).x, (float)sf::Mouse::getPosition(m_window).y);
}

int Game::randi_range(int min, int max)
{
	return (rand() % (1 + max - min)) + min;
}

bool Game::is_colliding(const Entity& e1, const Entity& e2)
{
	return e1.cTransform->position.distance_to_squared(e2.cTransform->position) <= ((e1.cCollision->radius + e2.cCollision->radius) * (e1.cCollision->radius + e2.cCollision->radius));
}
