#pragma once
#include "Entity.h"
#include "Vec2.h"

struct Intersect { bool result; Vec2 pos; };
class Physics
{
public:
	Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b);
	Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b);
	Vec2 ResolveCollision(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b);

	Intersect LineIntersect(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d);
	bool EntityIntersect(const Vec2& a, const Vec2& b, std::shared_ptr<Entity> e);
	Intersect CloserEntityIntersect(const Vec2& a, const Vec2& b, std::shared_ptr<Entity> origin, std::shared_ptr<Entity> e);
};