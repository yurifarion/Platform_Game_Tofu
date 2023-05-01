#include "AnimatorMachine.h"


AnimatorMachine::AnimatorMachine()
{

}
AnimatorMachine::AnimatorMachine(Sprite& currentsprite)
	:m_currentSprite(currentsprite)
{
	std::cout << "First Memory adress: " << &currentsprite << "\n";
}
void AnimatorMachine::addAnimation(Animation& anim)
{
	m_animations[anim.getName()] = anim;

	//Mudar isso para o set animation em caso de ter mais de uma animacao
	m_currentAnimation = anim;
	m_framecount = m_currentAnimation.getSprites().size() - 1;
}
void AnimatorMachine::update()
{
	m_currentframe++;

	if (m_currentframe > m_framecount) m_currentframe = 0;

	m_currentSprite = m_currentAnimation.getSprites()[m_currentframe];
}
bool AnimatorMachine::hasEnded()
{
	return false;
	///se nao for looping verificar se esta no ultimo frame
}
Sprite AnimatorMachine::getCurrentSprite()
{
	return m_currentSprite;
}