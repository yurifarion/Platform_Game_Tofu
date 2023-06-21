#include "ButtonUI.h"

ButtonUI::ButtonUI() {}

ButtonUI::ButtonUI(const RectTransform& recttransform)
	: m_recttransform(recttransform)
{
	m_hassprite = true;
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
	auto& pos = m_recttransform.getposition();
	auto& size = m_recttransform.getsize();
	//is mouse over button
	if (mousepos.x >= pos.x
		&& mousepos.x <= (pos.x + size.x)
		&& mousepos.y >= pos.y
		&& mousepos.y <= (pos.y + size.y))
		m_ismouseover = true;

	else m_ismouseover = false;
	
	if (m_ismouseover && sf::Mouse::isButtonPressed(sf::Mouse::Left)) m_ispressed = true;

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) m_ispressed = false;
}
