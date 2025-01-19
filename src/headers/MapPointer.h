/*
 * File:        MapPointer.h
 * Description: Represents way pointer before going as MapHero
 * 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        17.01.2025
 */

#pragma once

#include "IRenderable.h"
#include "Hex.h"

constexpr const char* POINTER_SPRITE_PATH = "media/sprites/map_pointer.png";
constexpr const char* POINTER_SPRITE_DANGER_PATH = "media/sprites/map_pointer_danger.png";
constexpr int MAP_POINTER_SIZE = 32;

class MapPointer : public IRenderable 
{
public:    
    virtual ~MapPointer() = default;

    void hide();

    void setPosition(const Hex& position, bool danger_tile);
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    Hex position_;
    std::string path_to_sprite_ = POINTER_SPRITE_PATH;
};