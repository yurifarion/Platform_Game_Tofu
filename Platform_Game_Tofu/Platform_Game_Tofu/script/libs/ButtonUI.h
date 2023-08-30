#pragma once
#include "Sprite.h"
#include "RectTransform.h"
#include <string>
#include <functional>

class ButtonUI
{
	RectTransform m_recttransform;
	bool m_hassprite = false;
	bool m_ismouseover = false;
	bool m_ispressed = false;
	bool m_isreleased = false;
	std::vector<std::function<void()>> m_listeners;

	void buttonclick();
public:

	ButtonUI();
	ButtonUI(const RectTransform& recttransform);
	bool ismouseover();
	bool ispressed();
	bool isreleased();
	void Update(const sf::RenderWindow& window);
	void addlistener(std::function<void()> listener);
};