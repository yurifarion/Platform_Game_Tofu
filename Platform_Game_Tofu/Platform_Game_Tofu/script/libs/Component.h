#pragma once

#include "Assets.h"
#include "AnimatorMachine.h"
#include "Rigidbody.h"

class Component
{
public:
	bool has = false;
};

class CTransform : public Component
{
public:
	Vec2 pos = { 0.0,0.0 };
	Vec2 prevPos = { 0.0,0.0 };
	Vec2 scale = { 1.0,1.0 };
	Vec2 velocity = { 0.0,0.0 };
	float angle = 0;

	CTransform()
		{}
	CTransform(const Vec2& p)
		:pos(p) {}
	CTransform(const Vec2& p, const Vec2& sp, const Vec2& sc, float a)
		:pos(p), prevPos(sp), scale(sc), angle(a)
	{}
	void flipX(bool isFaceLeft)
	{
		scale.x = isFaceLeft ? abs(scale.x) * -1 : abs(scale.x) * 1;
	}
	void move(Vec2 ppos)
	{
		prevPos = pos;
		pos += ppos;
	}

};

class CLifeSpan:public Component
{
public:
	int lifespan = 0;
	int frameCreated = 0;
	CLifeSpan() {}
	CLifeSpan(int duration, int frame)
		:lifespan(duration), frameCreated(frame) {}
};

class CInput : public Component
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;
	bool canshoot = false;
	bool canjump = false;

	CInput() {}
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox() {}
	CBoundingBox(const Vec2& s)
		:size(s), halfSize(s.x/2,s.y/2) {}
};

class CRigidbody : public Component
{
public:
	Rigidbody rigidbody;
	CRigidbody() {}
	CRigidbody(float grav)
	:rigidbody(Rigidbody(grav))
	{}
};

class CAnimator : public Component
{
public:
	AnimatorMachine animator;
	CAnimator(){}
	CAnimator(Sprite& currentsprite)
		:animator(AnimatorMachine(currentsprite)){}
};

class CSprite : public Component
{
public:
	Sprite sprite;
	bool smooth = false;
	CSprite() {}
	CSprite(const Sprite& psprite, bool r)
		:sprite(psprite), smooth(r) {}
};
class CState : public Component
{
public: 
	std::string state = "jumping";
	CState(){}
	CState(const std::string & s):state(s){}
};
class CUI : public Component
{
public:
	CUI() {}
};