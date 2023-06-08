
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
    void addSprite(const std::string& spritename, const std::string& textureName, Vec2& cellsize, Vec2& origin, Vec2& anchorsize);
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
              PLAYER = 1
            , ENEMY
            , GEM_BLUE
            , GEM_GREEN
            , GEM_RED
            , Tile_basic 
            , Tile_basic_grass
            , Tile_dirt_tl
            , Tile_dirt_tr
            , Tile_dirt_ctl
            , Tile_dirt_ctr
            , Tile_dirt_t
            , Tile_dirt_r
            , Tile_spike_d
            , Tile_dirt_tlrd
            , Tile_dirt_tlrdd
            , Tile_dirt_ld
            , Tile_dirt_rd
            , Tile_dirt_cld
            , Tile_dirt_crd
            , Tile_dirt_l
            , Tile_dirt_d
            , Tile_spike_l
            , Tile_darkbasic
            , Tile_darkbasic_grass
            , Tile_grass_l
            , Tile_grass_r
            , Tile_grass_ld
            , Tile_grass_d
            , Tile_grass_dr
            , Tile_grass_dlr
            , Tile_spike_t
            , Tile_darkdirt_tlrd
            , Tile_darkdirt_tlrdd
            , Tile_darkdirt_tl
            , Tile_darkdirt_tr
            , Tile_darkdirt_ctl
            , Tile_darkdirt_ctr
            , Tile_darkdirt_t
            , Tile_darkdirt_r
            , Tile_spike_r
            , Tile_darkdirt_ld
            , Tile_darkdirt_rd
            , Tile_darkdirt_cld
            , Tile_darkdirt_crd
            , Tile_darkdirt_l
            , Tile_darkdirt_d
            , Tile_black
            , Tile_darkestbasic
            , Tile_darkestbasic_grass
            , Tile_darkgrass_l
            , Tile_darkgrass_r
            , Tile_darkgrass_ld
            , Tile_darkgrass_d
            , Tile_darkgrass_dr
            , Tile_darkgrass_dlr
            , Tile_darkestdirt_tlrd
            , Tile_darkestdirt_tlrdd
            , Tile_darkestdirt_tl
            , Tile_darkestdirt_tr
            , Tile_darkestdirt_ctl
            , Tile_darkestdirt_ctr
            , Tile_darkestdirt_t
            , Tile_darkestdirt_r
            , Tile_darkestgrass_l
            , Tile_darkestgrass_r
            , Tile_darkestdirt_ld
            , Tile_darkestdirt_rd
            , Tile_darkestdirt_cld
            , Tile_darkestdirt_crd
            , Tile_darkestdirt_l
            , Tile_darkestdirt_d
            , Tile_clear
            , LAST
        };

        const int Count = 74;

        const std::string EnumToStr(SPRITEID sprite)
        {
            switch (sprite)
            {
            case SPRITEID::PLAYER:   return "Tofu_stand";
            case SPRITEID::ENEMY:   return "Enemy_stand";
            case SPRITEID::GEM_BLUE:   return "Gem_Blue_0";
            case SPRITEID::GEM_GREEN:   return "Gem_Green_0";
            case SPRITEID::GEM_RED:   return "Gem_Red_0";
            case SPRITEID::Tile_basic:   return "Tile_basic";
            case SPRITEID::LAST:   return "Tile";
            case SPRITEID::Tile_basic_grass:   return "Tile_basic_grass";
            case SPRITEID::Tile_dirt_tl: return "Tile_dirt_tl";
            case SPRITEID::Tile_dirt_tr: return "Tile_dirt_tr";
            case SPRITEID::Tile_dirt_ctl: return "Tile_dirt_ctl";
            case SPRITEID::Tile_dirt_ctr: return "Tile_dirt_ctr";
            case SPRITEID::Tile_dirt_t: return "Tile_dirt_t";
            case SPRITEID::Tile_dirt_r: return "Tile_dirt_r";
            case SPRITEID::Tile_spike_d: return "Tile_spike_d";
            case SPRITEID::Tile_dirt_tlrd: return "Tile_dirt_tlrd";
            case SPRITEID::Tile_dirt_tlrdd: return "Tile_dirt_tlrdd";
            case SPRITEID::Tile_dirt_ld: return "Tile_dirt_ld";
            case SPRITEID::Tile_dirt_rd: return "Tile_dirt_rd";
            case SPRITEID::Tile_dirt_cld: return "Tile_dirt_cld";
            case SPRITEID::Tile_dirt_crd: return "Tile_dirt_crd";
            case SPRITEID::Tile_dirt_l: return "Tile_dirt_l";
            case SPRITEID::Tile_dirt_d: return "Tile_dirt_d";
            case SPRITEID::Tile_spike_l: return "Tile_spike_l";
            case SPRITEID::Tile_darkbasic: return "Tile_darkbasic";
            case SPRITEID::Tile_darkbasic_grass: return "Tile_darkbasic_grass";
            case SPRITEID::Tile_grass_l: return "Tile_grass_l";
            case SPRITEID::Tile_grass_r: return "Tile_grass_r";
            case SPRITEID::Tile_grass_ld:   return "Tile_grass_ld";
            case SPRITEID::Tile_grass_d:   return "Tile_grass_d";
            case SPRITEID::Tile_grass_dr:   return "Tile_grass_dr";
            case SPRITEID::Tile_grass_dlr: return "Tile_grass_dlr";
            case SPRITEID::Tile_spike_t: return "Tile_spike_t";
            case SPRITEID::Tile_darkdirt_tlrd: return "Tile_darkdirt_tlrd";
            case SPRITEID::Tile_darkdirt_tlrdd: return "Tile_darkdirt_tlrdd";
            case SPRITEID::Tile_darkdirt_tl: return "Tile_darkdirt_tl";
            case SPRITEID::Tile_darkdirt_tr: return "Tile_darkdirt_tr";
            case SPRITEID::Tile_darkdirt_ctl: return "Tile_darkdirt_ctl";
            case SPRITEID::Tile_darkdirt_ctr: return "Tile_darkdirt_ctr";
            case SPRITEID::Tile_darkdirt_t: return "Tile_darkdirt_t";
            case SPRITEID::Tile_darkdirt_r: return "Tile_darkdirt_r";
            case SPRITEID::Tile_spike_r: return "Tile_spike_r";
            case SPRITEID::Tile_darkdirt_ld: return "Tile_darkdirt_ld";
            case SPRITEID::Tile_darkdirt_rd: return "Tile_darkdirt_rd";
            case SPRITEID::Tile_darkdirt_cld: return "Tile_darkdirt_cld";
            case SPRITEID::Tile_darkdirt_crd: return "Tile_darkdirt_crd";
            case SPRITEID::Tile_darkdirt_l: return "Tile_darkdirt_l";
            case SPRITEID::Tile_darkdirt_d: return "Tile_darkdirt_d";
            case SPRITEID::Tile_black: return "Tile_black";
            case SPRITEID::Tile_darkestbasic: return "Tile_darkestbasic";
            case SPRITEID::Tile_darkestbasic_grass: return "Tile_darkestbasic_grass";
            case SPRITEID::Tile_darkgrass_l:   return "Tile_darkgrass_l";
            case SPRITEID::Tile_darkgrass_r:   return "Tile_darkgrass_r";
            case SPRITEID::Tile_darkgrass_ld:   return "Tile_darkgrass_ld";
            case SPRITEID::Tile_darkgrass_d: return "Tile_darkgrass_d";
            case SPRITEID::Tile_darkgrass_dr: return "Tile_darkgrass_dr";
            case SPRITEID::Tile_darkgrass_dlr: return "Tile_darkgrass_dlr";
            case SPRITEID::Tile_darkestdirt_tlrd: return "Tile_darkestdirt_tlrd";
            case SPRITEID::Tile_darkestdirt_tlrdd: return "Tile_darkestdirt_tlrdd";
            case SPRITEID::Tile_darkestdirt_tl: return "Tile_darkestdirt_tl";
            case SPRITEID::Tile_darkestdirt_tr: return "Tile_darkestdirt_tr";
            case SPRITEID::Tile_darkestdirt_ctl: return "Tile_darkestdirt_ctl";
            case SPRITEID::Tile_darkestdirt_ctr: return "Tile_darkestdirt_ctr";
            case SPRITEID::Tile_darkestdirt_t: return "Tile_darkestdirt_t";
            case SPRITEID::Tile_darkestdirt_r: return "Tile_darkestdirt_r";
            case SPRITEID::Tile_darkestgrass_l: return "Tile_darkestgrass_l";
            case SPRITEID::Tile_darkestgrass_r: return "Tile_darkestgrass_r";
            case SPRITEID::Tile_darkestdirt_ld: return "Tile_darkestdirt_ld";
            case SPRITEID::Tile_darkestdirt_rd: return "Tile_darkestdirt_rd";
            case SPRITEID::Tile_darkestdirt_cld: return "Tile_darkestdirt_cld";
            case SPRITEID::Tile_darkestdirt_crd: return "Tile_darkestdirt_crd";
            case SPRITEID::Tile_darkestdirt_l: return "Tile_darkestdirt_l";
            case SPRITEID::Tile_darkestdirt_d: return "Tile_darkestdirt_d";
            case SPRITEID::Tile_clear: return "Tile_clear";
            }
        }
    };
    SpriteIDReference spriteRef;
};
