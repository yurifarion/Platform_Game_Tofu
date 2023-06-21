#include "TextUI.h"

TextUI::TextUI() {}

TextUI::TextUI(const std::string& text, const sf::Color& color)
	: m_text(text), m_color(color){}

const sf::Color& TextUI::getcolor()
{
	return m_color;
}
const std::string TextUI::gettext()
{
	return m_text;
}
float TextUI::getfontsize()
{
	return m_fontsize;
}
void TextUI::setfontsize(float fontsize)
{
	m_fontsize = fontsize;
}