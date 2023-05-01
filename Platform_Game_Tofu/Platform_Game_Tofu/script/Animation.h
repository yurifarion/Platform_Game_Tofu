#pragma once
#include "Sprite.h"

typedef std::vector<Sprite> SpriteVec;

class Animation
{
	SpriteVec m_sprites;
	size_t m_frameCount = 1;
	size_t m_currentFrame = 0;
	size_t m_speed = 0;
	std::string m_name = "none";
public:
	Animation();
	Animation(const std::string& name,const SpriteVec& sprites, const size_t speed);
	const std::string& getName() const;
	SpriteVec& getSprites();
};