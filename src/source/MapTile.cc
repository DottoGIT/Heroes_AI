/*
 * File:        MapTile.cc
 * Description: Contains data about single tile in map.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#include "MapTile.h"
#include "SymbolsTranslator.h"
#include "Logger.h"

void MapTile::setPosition(Hex position)
{
    position_ = position;
}

void MapTile::setWalkable(bool is_walkable)
{
    is_walkable_ = is_walkable;
}

void MapTile::setInteractable(std::shared_ptr<IInteractable> interactable)
{
    interactable_ = interactable;
    interactable->setPosition(position_);
}

IInteractable* MapTile::getInteractable()
{
    return interactable_.get();
}


const IInteractable* MapTile::getConstInteractable() const
{
    return interactable_.get();
}

void MapTile::setSymbol(char symbol)
{
    symbol_ = symbol;
}

char MapTile::getSymbol() const
{
    return symbol_;
}

Hex MapTile::getPosition() const
{
    return position_;
}


bool MapTile::isWalkable() const
{
    return is_walkable_;   
}

const std::string& MapTile::getSpritePath() const
{
    return SymbolsTranslator::symbolsToPaths[symbol_];
}

Hex MapTile::getSpriteDimensions() const
{
    return Hex(MAP_TILE_SIZE, MAP_TILE_SIZE);
}

int MapTile::getSpritePriority() const
{
    return BACKGROUND_PRIORTITY;
}

bool MapTile::isFlipped() const
{
    return false;
}

bool MapTile::interact()
{
    if(!interactable_)
    {
        return false;
    }

    bool delete_after_interaction = interactable_->interact();

    if(delete_after_interaction)
    {
        interactable_ = nullptr;
    }

    return true;
}