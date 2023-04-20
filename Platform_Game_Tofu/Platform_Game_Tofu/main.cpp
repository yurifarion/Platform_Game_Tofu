#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	Game g("Config.txt");
	g.run();
}

//TODO 
//Create enemies from Config.txt
//Create bullets from Config.txt