#include "RectTransform.h"

RectTransform::RectTransform() {}

RectTransform::RectTransform(const Vec2& pos, const Vec2& size)
	:  m_pos(pos), m_size(size),m_screenpos(pos) {}

RectTransform::RectTransform(const Vec2& pos, const Vec2& size, RectTransform* parent)
	: m_pos(pos), m_size(size), m_screenpos(pos), m_parent(parent)
{
	if (m_parent != NULL)
	{
		m_pos = pos + m_parent->getposition();
		m_scale = m_parent->getscale();
	}
}

bool RectTransform::isActive()
{
	return m_active;
}

void RectTransform::SetActive(bool active)
{
	m_active = active;
}
bool RectTransform::isVisible()
{
	if (m_parent != NULL)
	{
		if (!m_parent->isActive() || !m_active) return false;
		return m_visible;
	}
	else
	{
		return (m_active && m_visible);
	}
}
void RectTransform::SetVisible(bool visible)
{
	m_visible = visible;
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
const Vec2& RectTransform::getsize()
{
	return m_size;
}
void RectTransform::setsize(const Vec2& size)
{
	m_size = size;
}
const Vec2& RectTransform::getscale()
{
	return m_scale;
}
void RectTransform::setscale(const Vec2& scale)
{
	Vec2 scalep;

	if (m_parent != NULL) scalep = scale + m_parent->getscale();
	else scalep = scale;

	m_scale = scalep;
}
const RectTransform* RectTransform::getparent()
{
	return m_parent;
}

void RectTransform::setparent(RectTransform* parent)
{
	m_parent = parent;
}
