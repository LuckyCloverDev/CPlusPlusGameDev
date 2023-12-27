#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>

#include "Vector2.hpp"
#include "Game.hpp"

int main()
{
	srand((unsigned int)time(NULL));

	Game geometryWars;
	geometryWars.run();
	
	return 0;
}