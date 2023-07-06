#include "ImageUI.h"

ImageUI::ImageUI(){}

ImageUI::ImageUI(const Sprite& sprite, const RectTransform& recttransform)
	: m_image(sprite), m_recttransform(recttransform)
	{
		m_hassprite = true;

		m_image.getSprite().setScale(
			m_recttransform.getsize().x / m_image.getSprite().getLocalBounds().width,
			m_recttransform.getsize().y / m_image.getSprite().getLocalBounds().height);
	}
Sprite& ImageUI::getimage()
{
	return m_image;
}
void ImageUI::setimage(const Sprite& sprite)
{
	m_image = sprite;
	m_hassprite = true;

	m_image.getSprite().setScale(
		m_recttransform.getsize().x / m_image.getSprite().getLocalBounds().width,
		m_recttransform.getsize().y / m_image.getSprite().getLocalBounds().height);
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
