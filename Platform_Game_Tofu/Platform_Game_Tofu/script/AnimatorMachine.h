#pragma once
#include "Animation.h"

class AnimatorMachine
{
	std::map<std::string, Animation> m_animations;
	Sprite m_currentSprite;
	Animation m_currentAnimation;
	size_t m_framecount = 1;
	size_t m_currentframe = 0;
	bool m_hasEnd = false;
public:
	AnimatorMachine();
	AnimatorMachine(Sprite& currentsprite);
	void addAnimation(Animation& anim);
	void update();
	Sprite getCurrentSprite();
	bool hasEnded();
	void setAnimation(const std::string& name);
	bool isAnimationPlaying(const std::string& name);
};