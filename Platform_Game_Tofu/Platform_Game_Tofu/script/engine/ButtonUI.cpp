#include "ButtonUI.h"

ButtonUI::ButtonUI() {}

ButtonUI::ButtonUI(const Sprite& sprite, const RectTransform& recttransform)
	: m_image(sprite), m_recttransform(recttransform)
{
	m_hassprite = true;
}
ButtonUI::ButtonUI(const Vec2& size, const RectTransform& recttransform)
	: m_size(size), m_recttransform(recttransform) {}

Sprite& ButtonUI::getimage()
{
	return m_image;
}
Vec2& ButtonUI::getsize()
{
	return m_size;
}
sf::Color ButtonUI::getcolor()
{
	return m_color;
}
void ButtonUI::setcolor(const sf::Color& color)
{
	m_color = color;
}
bool ButtonUI::hassprite()
{
	return m_hassprite;
}
bool ButtonUI::ismouseover()
{
	return m_ismouseover;
}
bool ButtonUI::ispressed()
{
	return m_ispressed;
}
void ButtonUI::Update(const sf::RenderWindow& window)
{
	Vec2 mousepos = Vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	//is mouse over button
	if (mousepos.x >= m_recttransform.getposition().x
		&& mousepos.x <= (m_recttransform.getposition().x + getsize().x)
		&& mousepos.y >= m_recttransform.getposition().y
		&& mousepos.y <= (m_recttransform.getposition().y + getsize().y))
		m_ismouseover = true;

	else m_ismouseover = false;
	
	if (m_ismouseover && sf::Mouse::isButtonPressed(sf::Mouse::Left)) m_ispressed = true;

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) m_ispressed = false;
}
