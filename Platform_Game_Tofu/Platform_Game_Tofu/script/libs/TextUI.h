#pragma once
#include "Sprite.h"
#include <string>

class TextUI
{
	std::string m_text;
	sf::Color m_color;
	float m_fontsize = 12;
public:

	TextUI();
	TextUI(const std::string& text, const sf::Color& color);
	
	const sf::Color& getcolor();
	void setcolor(const sf::Color& color);
	const std::string gettext();
	float getfontsize();
	void setfontsize(float fontsize);
};