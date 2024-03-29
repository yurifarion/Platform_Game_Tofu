#pragma once

#include "Assets.h"
#include "ButtonUI.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "RectTransform.h"
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
	std::string m_name = "";
	float angle = 0;
	bool isFaceLeft = false;

	CTransform()
		{}
	CTransform(const Vec2& p)
		:pos(p) {}
	CTransform(const Vec2& p, const Vec2& sp, const Vec2& sc, float a)
		:pos(p), prevPos(sp), scale(sc), angle(a)
	{}
	void flipX(bool isFaceLeftp)
	{
		isFaceLeft = isFaceLeftp;
		scale.x = isFaceLeft ? abs(scale.x) * -1 : abs(scale.x) * 1;
	}
	void move(Vec2 ppos)
	{
		prevPos = pos;
		pos += ppos;
	}
	void setname(const std::string& name)
	{
		m_name = name;
	}
	const std::string& getname()
	{
		return m_name;
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
	bool dash = false;
	bool shoot = false;
	bool canshoot = false;
	bool canjump = false;

	CInput() {}
};
class CPlayer : public Component
{
	float maxdashenergy = 0;
public:
	int lifeamount = 3;
	int dashamount = 3;
	float speed = 0;
	float jumpforce = 0;
	float dashforce = 0;
	float dashenergy = 0;
	int gemscollected = 0;
	CPlayer() {}
	CPlayer(const float s, const float j, const float d,const float de)
		:speed(s), jumpforce(j), dashforce(d), dashenergy(de)
	{
		maxdashenergy = dashenergy;
	}

	void addDash(float amount)
	{
		dashenergy = std::clamp(dashenergy + amount, 0.0f, maxdashenergy);
	}
	void reducelife(int amout)
	{
		lifeamount += amout;
	}
	void reducedash(int amout)
	{
		dashamount += amout;
	}
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
	bool visible = true;
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
	std::string name = "NONE";
	RectTransform recttransform;
	CUI() {}
	CUI(const std::string& n, const Vec2& pos, const Vec2& scale) 
		:name(n),recttransform(RectTransform(pos,scale)) {}
	CUI(const std::string& n, const Vec2& pos, const Vec2& scale, RectTransform* parent)
		:name(n), recttransform(RectTransform(pos, scale,parent)) {}
}; 
class CImageUI : public Component
{
public:
	ImageUI imgui;
	CImageUI() {}
	CImageUI(const Sprite& image, const RectTransform& rect)
		:imgui(ImageUI(image,rect)) {}
};
class CButtonUI : public Component
{
public:
	ButtonUI buttonui;
	CButtonUI() {}
	CButtonUI(const RectTransform& rect)
		:buttonui(ButtonUI(rect)) {}
};
class CTextUI : public Component
{
public:
	TextUI textui;
	CTextUI() {}
	CTextUI(const std::string& text, const sf::Color& color = sf::Color::White)
		:textui(TextUI(text,color)) {}
};
class CTileMap : public Component
{
public:
	int spriteID = 0;
	CTileMap() {}
	CTileMap(const int si) :spriteID(si) {}
};
class CEnemyAI : public Component
{
public:
	bool rightinput = true;
	bool leftinput = false;
	float speed = 5.0f;
	CEnemyAI() {}
};
