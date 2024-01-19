#include "GameEngine.hpp"

GameEngine::GameEngine(const std::string& path)
{
	std::cout << "CREATED ENGINE INSTANCE" << std::endl;
	m_input = Input();
	init(path);
}

void GameEngine::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string temp;

	while (fin >> temp)
	{
		std::cout << "Loading " << temp << std::endl;
		if (temp.compare("Texture") == 0)
		{
			std::string name, location;

			fin >> name >> location;

			m_assets.addTexture(name, location);
		}
		else if (temp.compare("Animation") == 0)
		{
			std::string name, texture;
			size_t frames, speed;

			fin >> name >> texture >> frames >> speed;

			m_assets.addAnimation(name, Animation(name, m_assets.getTexture(texture), frames, speed));
		}
		else if (temp.compare("Font") == 0)
		{
			std::string name, location;

			fin >> name >> location;

			m_assets.addFont(name, location);
		}
	}

	std::cout << "CREATED WINDOW" << std::endl;
	m_window.create(sf::VideoMode(1280, 768), "Game Engine");
	m_window.display();
	std::cout << "SETTING FRAME LIMIT" << std::endl;
	m_window.setVerticalSyncEnabled(true);
	m_window.setFramerateLimit(60);


	std::cout << "Swapping scenes" << std::endl;
	changeScene("SCENE", std::make_shared<Scene_Play>(this, "level.txt"));
}

void GameEngine::update()
{
	m_delta = m_clock.restart().asSeconds();

	sUserInput();

	getScene(m_currentScene)->update();
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_sceneMap[m_currentScene];
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}

Assets& GameEngine::assets()
{
	return m_assets;
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}

void GameEngine::run()
{
	while (isRunning())
	{
		update();
	}
}

void GameEngine::sUserInput()
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
					process_button(BUTTON_UP, sf::Keyboard::Up);
					process_button(BUTTON_DOWN, sf::Keyboard::Down);
					process_button(BUTTON_LEFT, sf::Keyboard::Left);
					process_button(BUTTON_RIGHT, sf::Keyboard::Right);

					process_button(BUTTON_LEFT_SHIFT, sf::Keyboard::LShift);
					process_button(BUTTON_RIGHT_SHIFT, sf::Keyboard::RShift);

					process_button(BUTTON_A, sf::Keyboard::A);
					process_button(BUTTON_B, sf::Keyboard::B);
					process_button(BUTTON_C, sf::Keyboard::C);
					process_button(BUTTON_D, sf::Keyboard::D);
					process_button(BUTTON_E, sf::Keyboard::E);
					process_button(BUTTON_F, sf::Keyboard::F);
					process_button(BUTTON_G, sf::Keyboard::G);
					process_button(BUTTON_H, sf::Keyboard::H);
					process_button(BUTTON_I, sf::Keyboard::I);
					process_button(BUTTON_J, sf::Keyboard::J);
					process_button(BUTTON_K, sf::Keyboard::K);
					process_button(BUTTON_L, sf::Keyboard::L);
					process_button(BUTTON_M, sf::Keyboard::M);
					process_button(BUTTON_N, sf::Keyboard::N);
					process_button(BUTTON_O, sf::Keyboard::O);
					process_button(BUTTON_P, sf::Keyboard::P);
					process_button(BUTTON_Q, sf::Keyboard::Q);
					process_button(BUTTON_R, sf::Keyboard::R);
					process_button(BUTTON_S, sf::Keyboard::S);
					process_button(BUTTON_T, sf::Keyboard::T);
					process_button(BUTTON_U, sf::Keyboard::U);
					process_button(BUTTON_V, sf::Keyboard::V);
					process_button(BUTTON_W, sf::Keyboard::W);
					process_button(BUTTON_X, sf::Keyboard::X);
					process_button(BUTTON_Y, sf::Keyboard::Y);
					process_button(BUTTON_Z, sf::Keyboard::Z);
				}
				if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }
				const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
				currentScene()->sDoAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
			} break;
		}
	}
}

std::shared_ptr<Scene> GameEngine::getScene(const std::string& sceneName)
{
	return m_sceneMap[sceneName];
}

void GameEngine::changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	m_sceneMap[sceneName] = scene;
	m_currentScene = sceneName;
}