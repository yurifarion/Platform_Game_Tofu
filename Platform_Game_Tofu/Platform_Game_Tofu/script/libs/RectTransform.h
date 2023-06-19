#pragma once
#include "Sprite.h"
#include <string>

class RectTransform
{
	Vec2 m_pos;
	Vec2 m_scale;
	float m_angle = 0.0f;
	bool m_active = true;

public:

	RectTransform();
	RectTransform(const Vec2& pos, const Vec2& scale);

	bool isActive();
	void SetActive(bool active);
	const Vec2& getposition();
	void setposition(const Vec2& pos);
	const Vec2& getscale();
	const float getangle();
};