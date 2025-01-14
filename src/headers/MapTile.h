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



class MapTile : public IRenderable {
public:
    MapTile() = default;
    virtual ~MapTile() = default;

    bool interact();
    const IInteractable* getInteractable() const;

    void setPosition(Hex position);
    void setInteractable(std::shared_ptr<IInteractable> interactable);
    void setSymbol(char symbol);
    char getSymbol() const;
    
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    char symbol_;
    Hex position_;
    std::shared_ptr<IInteractable> interactable_;
};
