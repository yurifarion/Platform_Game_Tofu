#include "Animation.h"
#include <cmath>

Animation::Animation() {}

Animation::Animation(const std::string& name, const size_t speed, const bool isLoop)
	:m_name(name), m_speed(speed), isLoop(isLoop)
{
	
}
Animation::Animation(const std::string& name, const SpriteVec& sprites, const size_t speed, const bool isLoop)
	:m_name(name), m_sprites(sprites), m_speed(speed), isLoop(isLoop)
{
	
}
void Animation::addFrame(const Sprite& frame)
{
	m_sprites.push_back(frame);
}
const std::string& Animation::getName()const
{
	return m_name;
}
const size_t Animation::getSpeed() const
{
	return m_speed;
}
void Animation::setfixedduration(size_t duration)
{
	m_fixedduration = duration;
	cooldown = duration;
}
const size_t Animation::getfixedduration()
{
	return m_fixedduration;
}
SpriteVec& Animation::getSprites()
{
	return m_sprites;
}