#pragma once
#include "Sprite.h"

typedef std::vector<Sprite> SpriteVec;

class Animation
{
	SpriteVec m_sprites;
	size_t m_frameCount = 1;
	size_t m_currentFrame = 0;
	size_t m_speed = 0;
	size_t m_fixedduration = 0;
	std::string m_name = "none";
public:
	size_t cooldown = 0;
	bool isLoop = true;

	Animation();
	Animation(const std::string& name, const size_t speed,const bool isLoop = true);
	Animation(const std::string& name,const SpriteVec& sprites, const size_t speed,const bool isLoop = true);
	void addFrame(const Sprite& frame);
	const std::string& getName() const;
	const size_t getSpeed() const;
	void setfixedduration(size_t duration);
	const size_t getfixedduration();
	SpriteVec& getSprites();
};