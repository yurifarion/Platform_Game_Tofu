#include "RectTransform.h"

RectTransform::RectTransform() {}

RectTransform::RectTransform(const Vec2& pos, const Vec2& scale)
	:  m_pos(pos), m_scale(scale),m_screenpos(pos) {}

RectTransform::RectTransform(const Vec2& pos, const Vec2& scale, const RectTransform& parent)
	: m_pos(pos), m_scale(scale), m_screenpos(pos), m_parent(std::make_shared<RectTransform>(parent))
{
	if (m_parent != NULL)	m_pos = pos + m_parent->getposition();
}

bool RectTransform::isActive()
{
	return m_active;
}

void RectTransform::SetActive(bool active)
{
	m_active = active;
}
const Vec2& RectTransform::getposition()
{
	return m_pos;
}
void RectTransform::setposition(const Vec2& pos)
{
	Vec2 position;

	if (m_parent != NULL) position = pos + m_parent->getposition();
	else position = pos;

	m_pos = position;
}
const Vec2& RectTransform::getscreenposition()
{
	return m_screenpos;
}
void RectTransform::setscreenposition(const Vec2& pos)
{
	m_screenpos = pos;
}
const float RectTransform::getangle()
{
	return m_angle;
}
const Vec2& RectTransform::getscale()
{
	return m_scale;
}
const std::shared_ptr<RectTransform> RectTransform::getparent()
{
	if (m_parent == NULL) return std::shared_ptr<RectTransform>(this);
	return m_parent;
}

void RectTransform::setparent(const RectTransform parent)
{
	m_parent = std::make_shared<RectTransform>(parent);
}
