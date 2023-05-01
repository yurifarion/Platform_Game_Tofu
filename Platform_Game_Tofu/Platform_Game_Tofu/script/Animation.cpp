#include "Animation.h"
#include <cmath>

Animation::Animation() {}

Animation::Animation(const std::string& name, const SpriteVec& sprites, const size_t speed)
	:m_name(name), m_sprites(sprites), m_speed(speed)
{

}

const std::string& Animation::getName()const
{
	return m_name;
}
SpriteVec& Animation::getSprites()
{
	return m_sprites;
}