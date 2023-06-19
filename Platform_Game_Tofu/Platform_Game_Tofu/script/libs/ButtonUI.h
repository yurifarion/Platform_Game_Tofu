#pragma once
#pragma once
#include "Sprite.h"
#include "RectTransform.h"
#include <string>

class ButtonUI
{
	RectTransform m_recttransform;
	Sprite m_image;
	Vec2 m_size;
	sf::Color m_color = sf::Color(0, 0, 0, 200);
	bool m_hassprite = false;
	bool m_ismouseover = false;
	bool m_ispressed = false;

public:

	ButtonUI();
	ButtonUI(const Sprite& sprite, const RectTransform& recttransform);
	ButtonUI(const Vec2& size, const RectTransform& recttransform);
	Sprite& getimage();
	Vec2& getsize();
	sf::Color getcolor();
	void setcolor(const sf::Color& color);
	bool hassprite();
	bool ismouseover();
	bool ispressed();
	void Update(const sf::RenderWindow& window);
};