#include "PanelUI.h"

PanelUI::PanelUI(){}

PanelUI::PanelUI(const Sprite& psprite, const Vec2& pos, const Vec2& scale)
	: m_image(psprite),m_pos(pos), m_scale(scale) {}

bool PanelUI::isActive()
{
	return m_active;
}

void PanelUI::SetActive(bool active)
{
	m_active = active;
}
const Vec2& PanelUI::getposition()
{
	return m_pos;
}
void PanelUI::setposition(const Vec2& pos)
{
	m_pos = pos;
}
const float PanelUI::getangle()
{
	return m_angle;
}
const Vec2& PanelUI::getscale()
{
	return m_scale;
}
Sprite& PanelUI::getimage()
{
	return m_image;
}
void PanelUI::Update()
{

}