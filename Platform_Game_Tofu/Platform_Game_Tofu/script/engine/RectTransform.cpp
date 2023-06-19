#include "RectTransform.h"

RectTransform::RectTransform() {}

RectTransform::RectTransform(const Vec2& pos, const Vec2& scale)
	:  m_pos(pos), m_scale(scale) {}

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
	m_pos = pos;
}
const float RectTransform::getangle()
{
	return m_angle;
}
const Vec2& RectTransform::getscale()
{
	return m_scale;
}
