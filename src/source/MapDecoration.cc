/*
 * File:        MapDecoration.cc
 * Description: Represents map obstacles and non-interractive elements.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.01.2025
 */

#include "MapDecoration.h"
#include "SymbolsTranslator.h"

void MapDecoration::setPosition(const Hex& position)
{
    position_ = position;
}
void MapDecoration::setSymbol(char symbol)
{
    symbol_ = symbol;
}

char MapDecoration::getSymbol() const
{
    return symbol_;
}

Hex MapDecoration::getPosition() const
{
    return position_;
}

const std::string& MapDecoration::getSpritePath() const
{
    return SymbolsTranslator::symbolsToPaths[symbol_];
}

Hex MapDecoration::getSpriteDimensions() const
{
    return SymbolsTranslator::symbolsToSizes[symbol_];
}

int MapDecoration::getSpritePriority() const
{
    return OBJECT_PRIORTITY_2;
}

bool MapDecoration::isFlipped() const
{
    return false;
}
