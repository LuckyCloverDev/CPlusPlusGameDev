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

	sf::Font font;
	sf::Color font_color;
	unsigned int font_size;
	sf::Text text;

	float bg_offset = 0.f;
	for (int i = -2; i < 32; i++)
	{
		for (int j = -2; j < 18; j++)
		{
			if ((abs(i) % 2 == 0 && abs(j) % 2 == 0) || (abs(i) % 2 == 1 && abs(j) % 2 == 1))
			{
				continue;
			}
			std::shared_ptr<sf::RectangleShape> rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(40, 40));
			rect->setPosition(sf::Vector2f(i * 40, j * 40));
			rect->setFillColor(sf::Color(32, 32, 32));

			std::shared_ptr<Entity> entity = m_entities.addEntity("Background");
			entity->cShape->rectShape = rect;
		}
	}

	while (fin >> temp)
	{
		if (temp.compare("Window") == 0)
		{
			fin >> WINDOW_WIDTH >> WINDOW_HEIGHT >> FRAME_LIMIT >> FULLSCREEN;
		}
		else if (temp.compare("Font") == 0)
		{
			std::string font_file;
			int r, g, b;

			fin >> font_file >> font_size >> r >> g >> b;

			font.loadFromFile(font_file);
			font_color = sf::Color(r, g, b);

			text.setFont(font);
			text.setCharacterSize(font_size);
			text.setFillColor(font_color);
			text.setString(sf::String("Score: 0"));
			text.setPosition(sf::Vector2f(10, 0));
		}
		else if (temp.compare("Player") == 0)
		{
			// SPEEDS ARE FLOAT, REST ARE INT
			// Shape radius > col radius > speed > fill color > outline color > outline thickness > num vertices
		}
		else if (temp.compare("Enemy") == 0)
		{
			// Shape radius > col radius > min speed > max speed > outline color > outline thickness > min vertices > max vert > small lifespan > spawn interval
		}
		else if (temp.compare("Bullet") == 0)
		{
			// Shape radius > col radius > speed > fill color > outline color > outline thickness > num vertices > lifespan
		}
	}

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

	m_player = m_entities.addEntity("Player");
	m_player->cCollision = std::make_shared<CCollision>(5.f);
	m_player->cTransform = std::make_shared<CTransform>();
	m_player->cTransform->position = Vector2(640, 360);
}

void Game::process()
{
	sEnemySpawner();
	sUserInput();
	sMovement();
	sCollision();
	sRender();
}

void Game::sMovement()
{

}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				m_window.close();
			} break;

			case sf::Event::MouseButtonPressed:
			{
				printf("CLICKED\n");
			} break;

			case sf::Event::KeyPressed:
			{
				printf("Key pressed with code: %d\n", event.key.code);
				switch (event.key.code)
				{
					case sf::Keyboard::W:
					{
						printf("W\n");
					} break;

					case sf::Keyboard::A:
					{
						printf("A\n");
					} break;

					case sf::Keyboard::S:
					{
						printf("S\n");
					} break;

					case sf::Keyboard::D:
					{
						printf("D\n");
					} break;
				}
			} break;
		}
	}
}

void Game::sRender()
{
	m_window.clear();

	/*bg_offset += delta_time * 80.f;
	if (bg_offset >= 40)
	{
		for (auto& rect : bg_rects)
		{
			rect.move(sf::Vector2f(-bg_offset, -bg_offset));
		}
		bg_offset = 0.f;
	}

	for (auto& rect : bg_rects)
	{
		rect.move(sf::Vector2f(delta_time * 80.f, delta_time * 80.f));
		m_window.draw(rect);
	}
	m_window.draw(text);*/

	for (auto& entity : m_entities.getEntities())
	{
		if (entity->tag().compare("Background") == 0) continue;

		sf::CircleShape entity_shape(entity->cCollision->radius, 4);
		entity_shape.setOrigin(sf::Vector2f(entity->cCollision->radius, entity->cCollision->radius));
		entity_shape.setPosition(entity->cTransform->position.to_sf_vector());
		entity_shape.setFillColor(sf::Color(255, 0, 0));
		m_window.draw(entity_shape);
	}

	m_window.display();
}

void Game::sEnemySpawner()
{
	
}

void Game::sCollision()
{

}
