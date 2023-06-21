#pragma once
#include "Sprite.h"
#include <string>

class RectTransform
{
	Vec2 m_pos;
	Vec2 m_screenpos;
	Vec2 m_scale;
	float m_angle = 0.0f;
	bool m_active = true;
	std::shared_ptr<RectTransform> m_parent;

public:

	RectTransform();
	RectTransform(const Vec2& pos, const Vec2& scale);
	RectTransform(const Vec2& pos, const Vec2& scale, const RectTransform& parent);

	bool isActive();
	void SetActive(bool active);
	const Vec2& getposition();
	void setposition(const Vec2& pos);
	const Vec2& getscreenposition();
	void setscreenposition(const Vec2& pos);
	const Vec2& getscale();
	const float getangle();
	const std::shared_ptr<RectTransform> getparent();
	void setparent(const RectTransform parent);
};