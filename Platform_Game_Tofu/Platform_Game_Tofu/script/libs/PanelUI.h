#pragma once
#include "Sprite.h"
#include <string>

class PanelUI
{
	Sprite m_image;
	Vec2 m_size;

public:
	
	PanelUI();
	PanelUI(const Sprite& sprite);
	PanelUI(const Vec2& size);
	Sprite& getimage();
};