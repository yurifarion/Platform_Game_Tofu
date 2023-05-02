#include "Rigidbody.h"

Rigidbody::Rigidbody(){}

Rigidbody::Rigidbody(float gravity)
	:gravity(gravity) {}

const Vec2 Rigidbody::getAppliedForce()
{
	return m_appliedForce;
}
void Rigidbody::addForce(const Vec2& force)
{
	m_appliedForce += force;
}
void Rigidbody::setForce(const Vec2& force)
{
	m_appliedForce = force;
}
void Rigidbody::clearForce()
{
	m_appliedForce = Vec2(0, 0);
}
Vec2 Rigidbody::getVelocity(Vec2& maxvelocity)
{
	int Xsign = m_appliedForce.x > 0 ? 1 : -1;
    int Ysign = m_appliedForce.y > 0 ? 1 : -1;

	Vec2 result;
	
	result = m_appliedForce;

	if (abs(m_appliedForce.x) > abs(maxvelocity.x)) result.x = maxvelocity.x * Xsign;
	if (abs(m_appliedForce.y) > abs(maxvelocity.y)) result.y = maxvelocity.y * Ysign;


	return result;
}
void Rigidbody::update()
{
	//fps equals to 60
	m_gravityspeed += gravity/60;
	addForce(Vec2(0.0f, m_gravityspeed));
	if (isGrounded)
	{
		m_gravityspeed = 0;
		setForce(Vec2(0.0f, 0.0f));
	}
}