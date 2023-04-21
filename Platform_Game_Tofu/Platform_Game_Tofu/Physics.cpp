#include "Physics.h"
#include "Component.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b)
{
	//TODO return the overlap retangle size of the bounding boxes of entity a and b

	return Vec2(0, 0);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity>b)
{
	//TODO return the previous overlap rectangle size of the bounding boxes of entity a and b
	// previous overlap uses the entitys previous position

	return Vec2(0, 0);
}