#pragma once
#include "Sprite.h"
#include <string>

class PanelUI
{
	Vec2 m_pos;
	Vec2 m_scale;
	Sprite m_image;
	float m_angle = 0.0f;
	bool m_active =  true;
	//TODO SPRITE OR IMAGE

public:
	
	PanelUI();
	PanelUI(const Sprite& psprite, const Vec2& pos,const Vec2& scale);

	bool isActive();
	void SetActive(bool active);
	const Vec2& getposition();
	void setposition(const Vec2& pos);
	const Vec2& getscale();
	const float getangle();
	Sprite& getimage();
	void Update();
};