#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "Animation.h"

class Assets
{
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Texture> animations;
	std::map<std::string, sf::Sound> sounds;
	std::map<std::string, sf::Font> fonts;

public:
	void addTexture(std::string name, std::string path);
	void addAnimation(std::string name, std::string path);
	void addSound(std::string name, std::string path);
	void addFont(std::string name, std::string path);
	void loadFromFile(std::string path);

	sf::Texture& getTexture(std::string name);
	Animation& getAnimation(std::string name);
	sf::Sound& getSound(std::string name);
	sf::Font& getFont(std::string name);
};