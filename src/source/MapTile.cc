#include "MapTile.h"
#include "SymbolsTranslator.h"

void MapTile::setPosition(Hex position)
{
    position_ = position;
}

void MapTile::setInteractable(std::shared_ptr<IInteractable> interactable)
{
    interactable_ = interactable;
    interactable->setPosition(position_);
}

const IInteractable* MapTile::getInteractable() const
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

bool MapTile::interact()
{
    if(!interactable_)
    {
        return false;
    }

    interactable_->interact(*this);
    return true;
}
