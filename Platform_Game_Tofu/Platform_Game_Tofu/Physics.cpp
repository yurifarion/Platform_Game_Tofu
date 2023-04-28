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

	if (overlap.x > 0 && overlap.y > 0)
	{
		if (prevOverlap.x > 0)
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