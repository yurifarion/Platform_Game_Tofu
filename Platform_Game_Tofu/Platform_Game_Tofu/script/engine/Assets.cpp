#include "Assets.h"
#include <cassert>



Assets::Assets()
{

}

void Assets::loadFromFile(const std::string& path)
{
    std::ifstream file(path);
    std::string str;
    while (file.good())
    {
        file >> str;

        if (str == "Texture")
        {
            std::string name, path;
            bool smooth;
            file >> name >> path >> smooth;
            addTexture(name, path, smooth);
        }
        else if (str == "Sprite")
        {
            std::string name, texture;
            Vec2 cellsize, origin, anchorsize;
            file >> name >> texture >> cellsize.x>>cellsize.y>>origin.x>>origin.y>>anchorsize.x>>anchorsize.y;
            addSprite(name, texture, cellsize, origin,anchorsize);
        }
        else if (str == "Font")
        {
            std::string name, path;
            file >> name >> path;
            addFont(name, path);
        }
        else if (str == "Sound")
        {
            std::string name, path;
            file >> name >> path;
            addSoundBuffer(name, path);
        }
        else
        {
            std::cerr << "Unknown Asset Type: " << str << std::endl;
        }
      //  std::cout << "k: " << str
        //    << "\teof: " << file.eof()
        //    << "\tfail: " << file.fail()
        //    << "\tbad: " << file.bad()
        //    << "\tgood: " << file.good()
        //    << std::endl;
    }

}

void Assets::addTexture(const std::string& textureName, const std::string& path, bool smooth)
{
    m_textureMap[textureName] = sf::Texture();

    if (!m_textureMap[textureName].loadFromFile(path))
    {
        std::cerr << "Could not load texture file: " << path << std::endl;
        m_textureMap.erase(textureName);
    }
    else
    {
        m_textureMap[textureName].setSmooth(smooth);
        std::cout << "Loaded Texture: " << path << std::endl;
    }
}



const sf::Texture& Assets::getTexture(const std::string& textureName) const
{
    assert(m_textureMap.find(textureName) != m_textureMap.end());
    return m_textureMap.at(textureName);
}

void Assets::addSprite(const std::string& spritename, const std::string& textureName, Vec2& cellsize, Vec2& origin, Vec2& anchorsize)
{
    m_spriteMap[spritename] = Sprite(spritename, getTexture(textureName), cellsize, origin, anchorsize);
}

const Sprite& Assets::getSprite(const std::string& spritename) const
{
    if (m_spriteMap.find(spritename) == m_spriteMap.end()) {
        std::cout << "There is no sprite with "<< spritename <<" name\n";
    }
    assert(m_spriteMap.find(spritename) != m_spriteMap.end());
    return m_spriteMap.at(spritename);
}

void Assets::addFont(const std::string& fontName, const std::string& path)
{
    m_fontMap[fontName] = sf::Font();
    if (!m_fontMap[fontName].loadFromFile(path))
    {
        std::cerr << "Could not load font file: " << path << std::endl;
        m_fontMap.erase(fontName);
    }
    else
    {
        std::cout << "Loaded Font:    " << path << std::endl;
    }
}
void Assets::addSoundBuffer(const std::string& soundBufferName, const std::string& path)
{
    m_soundBufferMap[soundBufferName] = sf::SoundBuffer();
    if (!m_soundBufferMap[soundBufferName].loadFromFile(path))
    {
        std::cerr << "Could not load sound file: " << path << std::endl;
        m_soundBufferMap.erase(soundBufferName);
    }
    else
    {
        std::cout << "Loaded Sound:    " << path << std::endl;
    }
}
const sf::Font& Assets::getFont(const std::string& fontName) const
{
   assert(m_fontMap.find(fontName) != m_fontMap.end());
   return m_fontMap.at(fontName);
}
const sf::SoundBuffer& Assets::getSoundBuffer(const std::string& soundBufferName) const
{
    assert(m_soundBufferMap.find(soundBufferName) != m_soundBufferMap.end());
    return m_soundBufferMap.at(soundBufferName);
}
