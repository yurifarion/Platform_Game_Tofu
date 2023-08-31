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
bool ButtonUI::isreleased()
{
	return m_isreleased;
}
void ButtonUI::Update(const sf::RenderWindow& window)
{
	if (m_isreleased) m_isreleased = false;  
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
	
	if (m_ismouseover && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(!m_ispressed) buttonclick();
		m_ispressed = true;
	}

	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (m_ispressed)
		{
			m_isreleased = true;
		}
		m_ispressed = false;
	}
}
void ButtonUI::buttonclick()
{
	for (auto listener : m_listeners) {
		listener();
	}
}
void ButtonUI::addlistener(std::function<void()> listener)
{
	m_listeners.push_back(listener);
}
