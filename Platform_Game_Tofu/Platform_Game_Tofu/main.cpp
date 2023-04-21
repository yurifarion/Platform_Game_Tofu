#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include <iostream>

int main()
{
	GameEngine g("Config.txt");
	g.run();
}

//TODO 
//Create enemies from Config.txt
//Create bullets from Config.txt