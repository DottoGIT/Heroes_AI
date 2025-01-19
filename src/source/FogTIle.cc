#include "FogTile.h"

void FogTile::setPosition(Hex position)
{
    position_ = position;
}

void FogTile::setActive(bool active)
{
    is_active_ = active;
}

bool FogTile::isActive() const
{
    return is_active_;
}

const std::string& FogTile::getSpritePath() const
{
    return path_to_sprite_;
}

Hex FogTile::getSpriteDimensions() const
{
    return Hex(FOG_TILE_SIZE, FOG_TILE_SIZE);
}

int FogTile::getSpritePriority() const
{
    return OBJECT_PRIORTITY_4;
}

Hex FogTile::getPosition() const
{
    return position_;
}

bool FogTile::isFlipped() const
{
    return false;
}
