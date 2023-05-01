
#pragma once

#include "Common.h"
#include "Animation.h"

class Assets
{
    std::map<std::string, sf::Texture>      m_textureMap;
    std::map<std::string, Sprite>        m_spriteMap;
    std::map<std::string, sf::Font>         m_fontMap;

    void addTexture(const std::string& textureName, const std::string& path, bool smooth = true);
    void addSprite(const std::string& spritename, const std::string& textureName, Vec2& cellsize, Vec2& origin);
    void addFont(const std::string& fontName, const std::string& path);

public:

    Assets();

    void loadFromFile(const std::string& path);

    const sf::Texture& getTexture(const std::string& textureName) const;
    const Sprite& getSprite(const std::string& spritename) const;
    const sf::Font& getFont(const std::string& fontName) const;
};
