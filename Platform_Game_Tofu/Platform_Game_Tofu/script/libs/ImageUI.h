#pragma once
#include "Sprite.h"
#include "RectTransform.h"
#include <string>

class ImageUI
{
	Sprite m_image;
	sf::Color m_color = sf::Color(0,0,0,200);
	bool m_hassprite = false;
	RectTransform m_recttransform;

public:
	
	ImageUI();
	ImageUI(const Sprite& sprite,const RectTransform& recttransform);
	Sprite& getimage();
	sf::Color getcolor();
	void setimage(const Sprite& sprite);
	void setcolor(const sf::Color& color);
	bool hassprite();
};