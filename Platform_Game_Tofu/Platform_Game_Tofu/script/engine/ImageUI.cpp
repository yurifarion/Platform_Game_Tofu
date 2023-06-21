#include "ImageUI.h"

ImageUI::ImageUI(){}

ImageUI::ImageUI(const Sprite& sprite)
	: m_image(sprite) 
	{
		m_hassprite = true;
	}
Sprite& ImageUI::getimage()
{
	return m_image;
}
sf::Color ImageUI::getcolor()
{
	return m_color;
}
void ImageUI::setcolor(const sf::Color& color)
{
	m_color = color;
}
bool ImageUI::hassprite()
{
	return m_hassprite;
}
