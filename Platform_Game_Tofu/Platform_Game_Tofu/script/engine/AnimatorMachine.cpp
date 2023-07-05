#include "AnimatorMachine.h"


AnimatorMachine::AnimatorMachine()
{

}
AnimatorMachine::AnimatorMachine(Sprite& currentsprite)
	:m_currentSprite(currentsprite)
{
}
void AnimatorMachine::addAnimation(Animation& anim)
{
	m_animations[anim.getName()] = anim;

	m_framecount = m_currentAnimation.getSprites().size() - 1;
}
void AnimatorMachine::update()
{
	if (hasEnded()) return;

	//current fps is 60
	m_currentframe++;

	if (m_currentAnimation.getfixedduration() > 0) m_currentAnimation.cooldown -= 1;

	auto index = ((int)m_currentframe / (60 / m_currentAnimation.getSpeed()));


	if (index > m_framecount) {
		if (!m_currentAnimation.isLoop)
		{
			m_hasEnd = true;
			return;
		}
		m_currentframe = 0;
		index = 0;
	}
	

	m_currentSprite = m_currentAnimation.getSprites()[index];
}
bool AnimatorMachine::hasEnded()
{
	return m_hasEnd;
	///se nao for looping verificar se esta no ultimo frame
}
Sprite AnimatorMachine::getCurrentSprite()
{
	return m_currentSprite;
}
const Animation& AnimatorMachine::getCurrentAnimation()
{
	return m_currentAnimation;
}
void AnimatorMachine::setAnimation(const std::string& name)
{
	if (m_currentAnimation.cooldown <= 0)
	{
		if (isAnimationPlaying(name)) return;

		m_currentAnimation = m_animations[name];
		m_currentAnimation.cooldown = m_currentAnimation.getfixedduration();
		m_framecount = m_currentAnimation.getSprites().size() - 1;
		m_hasEnd = false;
	}
}
bool AnimatorMachine::isAnimationPlaying(const std::string& name)
{
	return (m_currentAnimation.getName() == name && !hasEnded());
}