#include "MapPointer.h"



void MapPointer::hide()
{
    position_ = Hex(-1,-1);
}

void MapPointer::setPosition(const Hex& position)
{
    position_ = position;
}

Hex MapPointer::getPosition() const
{
    return position_;
}

const std::string& MapPointer::getSpritePath() const
{
    return path_to_sprite_;
}

Hex MapPointer::getSpriteDimensions() const
{
    return Hex(MAP_POINTER_SIZE, MAP_POINTER_SIZE);
}

int MapPointer::getSpritePriority() const
{
    return OBJECT_PRIORTITY_3;
}

bool MapPointer::isFlipped() const
{
    return false;
}