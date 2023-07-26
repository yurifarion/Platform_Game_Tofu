#pragma once
#include "Sprite.h"
#include <string>

class TextUI
{
	std::string m_text;
	sf::Color m_color;
	sf::Color m_outlinecolor = sf::Color::Black;
	float m_outlinethickness = 0;
	float m_fontsize = 12;
public:

	TextUI();
	TextUI(const std::string& text, const sf::Color& color);
	
	const sf::Color& getcolor();
	void setcolor(const sf::Color& color);
	const sf::Color& getoutlinecolor();
	void setoutlinecolor(const sf::Color& color);
	void setoutlinethickness(float thickness);
	float getoutlinethickness();
	void settext(const std::string& text);
	const std::string gettext();
	float getfontsize();
	void setfontsize(float fontsize);
};