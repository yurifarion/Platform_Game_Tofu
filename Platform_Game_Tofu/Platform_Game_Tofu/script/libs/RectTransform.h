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
	bool m_visible = true;
	RectTransform* m_parent = nullptr;
	

public:
	enum class Align { topright, center , topcenter};
	Align alignment = Align::topright;

	RectTransform();
	RectTransform(const Vec2& pos, const Vec2& size);
	RectTransform(const Vec2& pos, const Vec2& size, RectTransform* parent);

	bool isActive();
	void SetActive(bool active);
	bool isVisible();
	void SetVisible(bool visible);
	const Vec2& getposition();
	void setposition(const Vec2& pos);
	const Vec2& getscreenposition();
	void setscreenposition(const Vec2& pos);
	const Vec2& getscale();
	void setscale(const Vec2& scale);
	const float getangle();
	const Vec2& getsize();
	void setsize(const Vec2& size);
	const RectTransform* getparent();
	void setparent(RectTransform* parent);
};