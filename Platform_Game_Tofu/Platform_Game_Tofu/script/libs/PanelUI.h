#pragma once
#include "Sprite.h"
#include <string>

class PanelUI
{
	Sprite m_image;
	Vec2 m_size;
	sf::Color m_color = sf::Color(0,0,0,200);
	bool m_hassprite = false;

public:
	
	PanelUI();
	PanelUI(const Sprite& sprite);
	PanelUI(const Vec2& size);
	Sprite& getimage();
	Vec2& getsize();
	sf::Color getcolor();
	void setcolor(sf::Color& color);
	bool hassprite();
};