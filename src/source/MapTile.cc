#include "MapTile.h"
#include "SymbolsToPaths.hpp"

void MapTile::setPosition(Hex position)
{
    position_ = position;
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

const std::string& MapTile::getSpritePath() const
{
    return SymbolsToPaths::symbols[symbol_];
}

Hex MapTile::getSpriteDimensions() const
{
    return Hex(MAP_TILE_WIDTH, MAP_TILE_HEIGHT);
}

int MapTile::getSpritePriority() const
{
    return BACKGROUND_PRIORTITY;
}

bool MapTile::isFlipped() const
{
    return false;
}
