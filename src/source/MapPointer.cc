#include "MapPointer.h"



void MapPointer::hide()
{
    position_ = Hex(-1,-1);
}

void MapPointer::setPosition(const Hex& position, bool danger_tile)
{
    position_ = position;
    if(danger_tile)
    {
        path_to_sprite_ = POINTER_SPRITE_DANGER_PATH;
    }
    else
    {
        path_to_sprite_ = POINTER_SPRITE_PATH;
    }
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