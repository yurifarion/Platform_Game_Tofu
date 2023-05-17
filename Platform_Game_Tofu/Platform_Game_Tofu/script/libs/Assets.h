
#pragma once

#include "Common.h"
#include "Animation.h"

class Assets
{
   

    std::map<std::string, sf::Texture>      m_textureMap;
    std::map<std::string, Sprite>        m_spriteMap;
    std::map<std::string, sf::Font>         m_fontMap;
    std::map<std::string, sf::SoundBuffer>         m_soundBufferMap;

    void addTexture(const std::string& textureName, const std::string& path, bool smooth = true);
    void addSprite(const std::string& spritename, const std::string& textureName, Vec2& cellsize, Vec2& origin);
    void addFont(const std::string& fontName, const std::string& path);
    void addSoundBuffer(const std::string& soundBufferName, const std::string& path);

public:

    Assets();
  
    void loadFromFile(const std::string& path);

    const sf::Texture& getTexture(const std::string& textureName) const;
    const Sprite& getSprite(const std::string& spritename) const;
    const sf::Font& getFont(const std::string& fontName) const;
    const sf::SoundBuffer& getSoundBuffer(const std::string& soundBufferName) const;

    struct SpriteIDReference {
        enum class SPRITEID {
            Tile
            , Tile_grass
            , Tile_grass_tl
            , Tile_grass_tr
            , Tile_grass_ll
            , Tile_grass_l
            , Tile_grass_lr
            , Tile_grass_ltlr
            , Tile_big_tl
            , Tile_big_tr
            , Tile_big_ll
            , Tile_big_lr
            , Tile_big_l
            , Tile_mini
            , Tile_tt
            , Tile_ll
            , Tile_l
            , Tile_r
            , bg_1_Tile
            , bg_1_Tile_l
            , bg_1_Tile_r
            , bg_1_shadow_ll
            , LAST
        };

        const int Count = 22;

        const std::string EnumToStr(SPRITEID sprite)
        {
            switch (sprite)
            {
            case SPRITEID::Tile:   return "Tile";
            case SPRITEID::LAST:   return "Tile";
            case SPRITEID::Tile_grass:   return "Tile_grass";
            case SPRITEID::Tile_grass_tl: return "Tile_grass_tl";
            case SPRITEID::Tile_grass_tr: return "Tile_grass_tr";
            case SPRITEID::Tile_grass_ll: return "Tile_grass_ll";
            case SPRITEID::Tile_grass_l: return "Tile_grass_l";
            case SPRITEID::Tile_grass_lr: return "Tile_grass_lr";
            case SPRITEID::Tile_grass_ltlr: return "Tile_grass_ltlr";
            case SPRITEID::Tile_big_tl: return "Tile_big_tl";
            case SPRITEID::Tile_big_tr: return "Tile_big_tr";
            case SPRITEID::Tile_big_ll: return "Tile_big_ll";
            case SPRITEID::Tile_big_lr: return "Tile_big_lr";
            case SPRITEID::Tile_big_l: return "Tile_big_l";
            case SPRITEID::Tile_mini: return "Tile_mini";
            case SPRITEID::Tile_tt: return "Tile_tt";
            case SPRITEID::Tile_ll: return "Tile_ll";
            case SPRITEID::Tile_l: return "Tile_l";
            case SPRITEID::Tile_r: return "Tile_r";
            case SPRITEID::bg_1_Tile: return "bg_1_Tile";
            case SPRITEID::bg_1_Tile_l: return "bg_1_Tile_l";
            case SPRITEID::bg_1_Tile_r: return "bg_1_Tile_r";
            case SPRITEID::bg_1_shadow_ll: return "bg_1_shadow_ll";
            }
        }
    };
    SpriteIDReference spriteRef;
};
