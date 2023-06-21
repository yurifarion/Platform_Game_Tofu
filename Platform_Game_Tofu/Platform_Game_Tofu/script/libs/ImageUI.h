#pragma once
#include "Sprite.h"
#include <string>

class ImageUI
{
	Sprite m_image;
	sf::Color m_color = sf::Color(0,0,0,200);
	bool m_hassprite = false;

public:
	
	ImageUI();
	ImageUI(const Sprite& sprite);
	Sprite& getimage();
	sf::Color getcolor();
	void setcolor(const sf::Color& color);
	bool hassprite();
};