#include "Animation.h"
#include <cmath>

Animation::Animation()
{

}

Animation::Animation(const std::string& name, const sf::Texture& t)
	:Animation(name, t, 1, 0)
{

}

Animation::Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed)
	:m_name(name)
	, m_sprite(t)
	, m_frameCount(frameCount)
	, m_currentFrame(0)
	, m_speed(speed)
{
	m_size = Vec2((float)t.getSize().x / frameCount, (float)t.getSize().y);
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect(std::floor(m_currentFrame) * m_size.x, 0, m_size.x, m_size.y));

}
Animation::Animation(const std::string& name, const sf::Texture& t, const Vec2& cellsize, const Vec2& origin, size_t frameCount, size_t speed, bool isVertical = false)
	:m_name(name)
	, m_sprite(t)
	, m_frameCount(frameCount)
	, m_currentFrame(0)
	, m_speed(speed)
{
	m_size = Vec2(cellsize.x, cellsize.y);
	m_sprite.setOrigin(cellsize.x / 2.0f, cellsize.y / 2.0f);

	if (!isVertical)
	{
		Vec2 pos;
		pos.x = m_size.x * origin.x;
		pos.y = cellsize.y * origin.y;
		m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, cellsize.x, cellsize.y));
	}
	else 
	{
		Vec2 pos;
		pos.x = cellsize.x * origin.x;
		pos.y = m_size.y * origin.y;
		m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, cellsize.x, cellsize.y));
	}

}

//Update the animaton to show the next frame depending on its speed
//animation loops when its reaches the end
void::Animation::update()
{
	//add the speed variable to the current frame
	m_currentFrame++;
	//TODO 1) calculate the correct frame of animation to play based on currentframe and speed
	//2) set the texture rectangle porperly (see constructor for smaple)
}
const Vec2& Animation::getSize() const
{
	return m_size;
}
const std::string& Animation::getName()const
{
	return m_name;
}
sf::Sprite& Animation::getSprite()
{
	return m_sprite;
}
bool Animation::hasEnded()const
{
	//TODO detect when animaton has ended (last frame was played) and return true
	return false;

}