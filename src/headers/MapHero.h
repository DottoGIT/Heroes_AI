/*
 * File:        MapHero.h
 * Description: Represents player army on the map
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2025
 */

#pragma once
#include <memory>
#include <string>
#include "IRenderable.h"
#include "IInteractable.h"
#include "Hex.h"

constexpr const char* HERO_SPRITE_PATH = "media/sprites/hero.png";
constexpr const int HERO_SPRITE_WIDTH = 32;
constexpr const int HERO_SPRITE_HEIGHT = 64;

class MapHero : public IRenderable {
public:
    MapHero() = default;
    virtual ~MapHero() = default;
    void setPosition(const Hex& position);
    void setFlip(bool is_flipped);
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    char symbol_;
    Hex position_;
    bool is_flipped_ = false;
    std::shared_ptr<IInteractable> interactable_;
    std::string path_to_sprite_ = HERO_SPRITE_PATH;
};
