#pragma once
#include "Entity.h"
#include "Vec2.h"

class Physics
{
public:
	const bool isCollision(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
	Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b);
	Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b);
};