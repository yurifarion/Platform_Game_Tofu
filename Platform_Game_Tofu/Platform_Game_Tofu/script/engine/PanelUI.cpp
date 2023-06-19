#include "PanelUI.h"

PanelUI::PanelUI(){}

PanelUI::PanelUI(const Sprite& sprite)
	: m_image(sprite) {}
PanelUI::PanelUI(const Vec2& size)
	: m_size(size) {}

Sprite& PanelUI::getimage()
{
	return m_image;
}
