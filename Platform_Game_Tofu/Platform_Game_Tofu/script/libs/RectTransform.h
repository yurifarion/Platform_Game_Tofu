#pragma once
#include "Sprite.h"
#include <string>

class RectTransform
{
	Vec2 m_pos = Vec2(0.0f,0.0f);
	Vec2 m_screenpos = Vec2(0.0f, 0.0f);
	Vec2 m_size = Vec2(0.0f, 0.0f);
	Vec2 m_scale = Vec2(1.0f, 1.0f);
	float m_angle = 0.0f;
	bool m_active = true;
	std::shared_ptr<RectTransform> m_parent;

public:

	RectTransform();
	RectTransform(const Vec2& pos, const Vec2& size);
	RectTransform(const Vec2& pos, const Vec2& size, const RectTransform& parent);

	bool isActive();
	void SetActive(bool active);
	const Vec2& getposition();
	void setposition(const Vec2& pos);
	const Vec2& getscreenposition();
	void setscreenposition(const Vec2& pos);
	const Vec2& getscale();
	const float getangle();
	const Vec2& getsize();
	void setsize(const Vec2& size);
	const std::shared_ptr<RectTransform> getparent();
	void setparent(const RectTransform parent);
};