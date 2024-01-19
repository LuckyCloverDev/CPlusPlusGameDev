#include "GameEngine.hpp"

int main()
{
	srand((unsigned int)time(NULL));

	GameEngine engine("assets.txt");
	engine.run();
	
	return 0;
}