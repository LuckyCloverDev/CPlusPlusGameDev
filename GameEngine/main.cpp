#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "Vector2.hpp"
#include "Game.hpp"

int main()
{
	srand((unsigned int)time(NULL));

	Game geometryWars;

	float delta_time = 0.016666f;
	sf::Clock clock;

	while (true)
	{
		
		delta_time = clock.restart().asSeconds();
		float fps = 1.f / delta_time;
		//sf::Mouse::getPosition(window);
		
		geometryWars.process();
	}
	
	return 0;
}