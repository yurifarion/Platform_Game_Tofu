#include "Vec2.h"
#include <math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	:x(xin),y(yin)
{

}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const float value) const
{
	
	return Vec2(x/value, y/value);
}

Vec2 Vec2::operator * (const float value) const
{
	
	return Vec2(x * value, y * value);
}

bool Vec2::operator == (const Vec2& rhs) const
{
		return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return (x != rhs.x || y != rhs.y);
}

void Vec2::operator += (const Vec2& rhs) 
{
	x += rhs.x;
	y += rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}

void Vec2::operator *= (const float value)
{
	x *= value;
	y *= value;
}

void Vec2::operator /= (const float value)
{
	x /= value;
	y /= value;
}

float Vec2::dist( const Vec2& rhs) const
{
	return sqrt(((rhs.x - x) * (rhs.x - x)) + ((rhs.y - y) * (rhs.y - y)));
}

float Vec2::length()const
{
	return sqrt(x*x + y*y);
}

Vec2 Vec2::normalized()const  
{
	return Vec2(x / length(), y / length());
}