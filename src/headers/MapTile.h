/*
 * File:        MapTile.h
 * Description: Contains data about single tile in map.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#pragma once

#include <memory>
#include <string>
#include "IRenderable.h"
#include "IInteractable.h"
#include "Hex.h"

constexpr int MAP_TILE_SIZE = 32;

class MapTile : public IRenderable
{
public:
    MapTile() = default;
    virtual ~MapTile() = default;

    bool interact();
    IInteractable* getInteractable();
    const IInteractable* getConstInteractable() const;

    void setPosition(Hex position);
    void setInteractable(std::shared_ptr<IInteractable> interactable);
    void setWalkable(bool is_walkable);
    void setSymbol(char symbol);
    char getSymbol() const;
    bool isWalkable() const;
    
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;

private:
    char symbol_;
    Hex position_;
    bool is_walkable_ = true;
    std::shared_ptr<IInteractable> interactable_;
};
