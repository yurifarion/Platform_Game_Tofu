#pragma once
#include <vector>
#include "Vec2.h"
#include <SFML/Graphics.hpp>

class Sprite
{
	sf::Sprite m_sprite;
	Vec2 m_size = { 1,1 };
	std::string m_name = "none";

public:
	Sprite();
	Sprite(const std::string& name, const sf::Texture& t);
	Sprite(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);
	Sprite(const std::string& name, const sf::Texture& t, const Vec2& cellsize, const Vec2& origin, size_t frameCount, size_t speed, bool isVertical);

	const std::string& getName() const;
	const Vec2& getSize() const;
	sf::Sprite& getSprite();
};