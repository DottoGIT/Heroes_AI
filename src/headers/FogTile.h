/*
 * File:        FogTile.h
 * Description: Represents Fog of War tile
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        19.01.2025
 */
#pragma once
#include "IRenderable.h"

constexpr int FOG_TILE_SIZE = 64;
constexpr char* PATH_TO_SPRITE = "media/sprites/fog.png";

class FogTile : public IRenderable
{
public:
    FogTile() = default;
    virtual ~FogTile() = default;
    void setPosition(Hex position);
    void setActive(bool active);
    
    bool isActive() const;
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    bool is_active_ = true;
    std::string path_to_sprite_ = PATH_TO_SPRITE;
    Hex position_;
};