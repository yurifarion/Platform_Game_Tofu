#pragma once
#include "Vec2.h"
#include <cmath>

class Rigidbody
{
	Vec2 m_appliedForce;
	float m_gravityspeed = 0;
	float m_groundFriction = 0.1f;//how much percent it lose per frame

public:
	float gravity = 0;
	bool isGrounded = false;
	bool isColliding = false;


	Rigidbody();
	Rigidbody(float gravity);

	const Vec2 getAppliedForce();
	void addForce(const Vec2& force);
	void setForce(const Vec2& force);
	void clearForce();
	Vec2 getVelocity(Vec2& maxvelocity);
	void update(float deltatime);
};