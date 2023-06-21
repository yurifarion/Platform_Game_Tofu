#pragma once
#include "Sprite.h"
#include "RectTransform.h"
#include <string>

class ButtonUI
{
	RectTransform m_recttransform;
	bool m_hassprite = false;
	bool m_ismouseover = false;
	bool m_ispressed = false;

public:

	ButtonUI();
	ButtonUI(const RectTransform& recttransform);
	bool ismouseover();
	bool ispressed();
	void Update(const sf::RenderWindow& window);
};