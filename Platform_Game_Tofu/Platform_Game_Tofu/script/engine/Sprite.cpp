#include "Sprite.h"
#include <cmath>

Sprite::Sprite()
{

}

Sprite::Sprite(const std::string& name, const sf::Texture& t)
	:m_name(name)
	, m_sprite(t)
{
	m_size = Vec2(t.getSize().x, t.getSize().y);
	m_sprite.setOrigin(t.getSize().x / 2.0f, t.getSize().y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect(0, 0, t.getSize().x, t.getSize().y));
}
Sprite::Sprite(const std::string& name, const sf::Texture& t, const Vec2& cellsize, const Vec2& origin, const Vec2& anchorsize)
	:m_name(name)
	, m_sprite(t)
{
	m_size = Vec2(cellsize.x, cellsize.y);
	m_sprite.setOrigin(cellsize.x / 2.0f, cellsize.y / 2.0f);

	Vec2 pos;
	pos.x = anchorsize.x * origin.x;
	pos.y = anchorsize.y * origin.y;
	m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, cellsize.x, cellsize.y));
}
const Vec2& Sprite::getSize() const
{
	return m_size;
}
const std::string& Sprite::getName()const
{
	return m_name;
}
sf::Sprite& Sprite::getSprite()
{
	return m_sprite;
}
