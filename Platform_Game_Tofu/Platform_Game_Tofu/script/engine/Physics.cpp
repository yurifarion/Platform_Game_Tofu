#include "Physics.h"
#include "Component.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b)
{
	auto apos = a->getComponent<CTransform>().pos;
	auto bpos = b->getComponent<CTransform>().pos;

	auto asize = a->getComponent<CBoundingBox>().size;
	auto bsize = b->getComponent<CBoundingBox>().size;

	Vec2 delta( abs(apos.x - bpos.x), abs(apos.y - bpos.y) );
	float ox = (asize.x / 2) + (bsize.x / 2) - delta.x;
	float oy = (asize.y / 2) + (bsize.y / 2) - delta.y;

	return Vec2(ox, oy);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b)
{
	auto apos = a->getComponent<CTransform>().prevPos;
	auto bpos = b->getComponent<CTransform>().pos;

	auto asize = a->getComponent<CBoundingBox>().size;
	auto bsize = b->getComponent<CBoundingBox>().size;

	Vec2 delta(abs(apos.x - bpos.x), abs(apos.y - bpos.y));
	float ox = (asize.x / 2) + (bsize.x / 2) - delta.x;
	float oy = (asize.y / 2) + (bsize.y / 2) - delta.y;

	return Vec2(ox, oy);
}
Vec2 Physics::ResolveCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b)
{
	auto overlap = GetOverlap(a, b);
	auto prevOverlap = GetPreviousOverlap(a, b);

	auto apos = a->getComponent<CTransform>().pos;
	auto bpos = b->getComponent<CTransform>().pos;

	if (overlap.x > 0)
	{
		if (prevOverlap.x > prevOverlap.y)
		{
			if (bpos.y < apos.y)
			{
				overlap.x = 0;
				overlap.y = overlap.y;
				return overlap;
			}
			else
			{
				overlap.x = 0;
				overlap.y = -overlap.y;
				return overlap;
			}
		}
		else if (prevOverlap.y > 0)
		{
			if (bpos.x < apos.x)
			{
				overlap.x = overlap.x;
				overlap.y = 0;
				return overlap;
			}
			else
			{
				overlap.x = -overlap.x;
				overlap.y = 0;
				return overlap;
			}
			
		}
		return Vec2(0, 0);
	}
}

Intersect Physics::LineIntersect(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d)
{
	Vec2 r = (b - a);
	Vec2 s = (d - c);
	float rxs = (r.x * s.y) - (r.y * s.x);
	Vec2 cma = c - a;
	float cmaxs = (cma.x * s.y) - (cma.y * s.x);
	float cmaxr = (cma.x * r.y) - (cma.y * r.x);
	float t = cmaxs / rxs;
	float u = cmaxr / rxs;

	if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
		return { true, Vec2(a.x + t * r.x,a.y + t * r.y) };
	else
		return { false, Vec2(0,0) };

}
bool Physics::EntityIntersect(const Vec2& a, const Vec2& b, std::shared_ptr<Entity> e)
{
	float halfWidth = e->getComponent<CBoundingBox>().size.x / 2;
	float halfHeight = e->getComponent<CBoundingBox>().size.y / 2;

	float posX = e->getComponent<CTransform>().pos.x;
	float posY = e->getComponent<CTransform>().pos.y;

	Vec2 ea = Vec2(posX - halfWidth, posY - halfHeight);
	Vec2 eb = Vec2(posX + halfWidth, posY - halfHeight);
	Vec2 ec = Vec2(posX - halfWidth, posY + halfHeight);
	Vec2 ed = Vec2(posX + halfWidth, posY + halfHeight);

	

	if (LineIntersect(a, b, ea, eb).result)
	{
		return true;
	}
	else if (LineIntersect(a, b, ea, ec).result)
	{
		return true;
	}
	else if (LineIntersect(a, b, eb, ed).result)
	{
		return true;
	}
	else if (LineIntersect(a, b, ec, ed).result)
	{
		return true;
	}

	return false;
}
Intersect Physics::CloserEntityIntersect(const Vec2& a, const Vec2& b, std::shared_ptr<Entity> origin, std::shared_ptr<Entity> e)
{
	Intersect closerIntersect;
	float distance = 0;

	float halfWidth = e->getComponent<CBoundingBox>().size.x / 2;
	float halfHeight = e->getComponent<CBoundingBox>().size.y / 2;

	float posX = e->getComponent<CTransform>().pos.x;
	float posY = e->getComponent<CTransform>().pos.y;

	Vec2 ea = Vec2(posX - halfWidth, posY - halfHeight);
	Vec2 eb = Vec2(posX + halfWidth, posY - halfHeight);
	Vec2 ec = Vec2(posX - halfWidth, posY + halfHeight);
	Vec2 ed = Vec2(posX + halfWidth, posY + halfHeight);



	if (LineIntersect(a, b, ea, eb).result)
	{
		distance = origin->getComponent<CTransform>().pos.dist(LineIntersect(a, b, ea, eb).pos);
		closerIntersect = LineIntersect(a, b, ea, eb);
	}
	else if (LineIntersect(a, b, ea, ec).result)
	{
		float newDistance = origin->getComponent<CTransform>().pos.dist(LineIntersect(a, b, ea, ec).pos);
		if (distance == 0)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, ea, ec);
		}
		else if (distance > newDistance)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, ea, ec);
		}
	}
	else if (LineIntersect(a, b, eb, ed).result)
	{
		float newDistance = origin->getComponent<CTransform>().pos.dist(LineIntersect(a, b, eb, ed).pos);
		if (distance == 0)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, eb, ed);
		}
		else if (distance > newDistance)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, eb, ed);
		}
	}
	else if (LineIntersect(a, b, ec, ed).result)
	{
		float newDistance = origin->getComponent<CTransform>().pos.dist(LineIntersect(a, b, ec, ed).pos);
		if (distance == 0)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, ec, ed);
		}
		else if (distance > newDistance)
		{
			distance = newDistance;
			closerIntersect = LineIntersect(a, b, ec, ed);
		}
	}

	return closerIntersect;
}