#include "PanelUI.h"

PanelUI::PanelUI(){}

PanelUI::PanelUI(const Sprite& sprite)
	: m_image(sprite) 
	{
	m_hassprite = true;
	}
PanelUI::PanelUI(const Vec2& size)
	: m_size(size) {}

Sprite& PanelUI::getimage()
{
	return m_image;
}
Vec2& PanelUI::getsize()
{
	return m_size;
}
sf::Color PanelUI::getcolor()
{
	return m_color;
}
void PanelUI::setcolor(sf::Color& color)
{
	m_color = color;
}
bool PanelUI::hassprite()
{
	return m_hassprite;
}
