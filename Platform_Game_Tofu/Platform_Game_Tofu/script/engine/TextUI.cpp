#include "TextUI.h"

TextUI::TextUI() {}

TextUI::TextUI(const std::string& text, const sf::Color& color)
	: m_text(text), m_color(color){}

const sf::Color& TextUI::getcolor()
{
	return m_color;
}
void TextUI::setcolor(const sf::Color& color)
{
	m_color = color;
}
const sf::Color& TextUI::getoutlinecolor()
{
	return m_outlinecolor;
}
void TextUI::setoutlinecolor(const sf::Color& color)
{
	m_outlinecolor = color;
}
void TextUI::setoutlinethickness(float thickness)
{
	m_outlinethickness = thickness;
}
float  TextUI::getoutlinethickness()
{
	return m_outlinethickness;
}
void TextUI::settext(const std::string& text)
{
	m_text = text;
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