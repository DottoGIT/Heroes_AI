#include "MapTile.h"
#include "SymbolsTranslator.h"

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
    return SymbolsTranslator::symbolsToPaths[symbol_];
}

Hex MapTile::getSpriteDimensions() const
{
    // Display has its own dimensions so this return changes nothing
    return Hex(0, 0);
}

int MapTile::getSpritePriority() const
{
    return BACKGROUND_PRIORTITY;
}

bool MapTile::isFlipped() const
{
    return false;
}
