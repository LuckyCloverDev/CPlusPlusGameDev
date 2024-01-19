#pragma once

#include "Input.hpp"
#include "Scene.hpp"
#include "Assets.hpp"
#include "Scene_Play.hpp"
#include "Scene_Menu.hpp"

#include <fstream>
#include <iostream>

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
	sf::RenderWindow             m_window;
	sf::Clock                    m_clock;
	Assets                       m_assets;
	std::string                  m_currentScene;
	SceneMap                     m_sceneMap;
	size_t                       m_simulationSpeed = 1;
	bool                         m_running = true;
	float                        m_delta = 0.01666f;

	Input                        m_input;

	void    init(const std::string& path);
	void    update();
	void    sUserInput();

	std::shared_ptr<Scene>  currentScene();
public:
	GameEngine(const std::string& path);

	std::shared_ptr<Scene> getScene(const std::string& sceneName);
	void changeScene(const std::string& sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);

	void quit() { m_running = false; }
	void run();

	sf::RenderWindow& window();
	Assets&           assets();
	bool              isRunning();
	float             delta() { return m_delta; }
};