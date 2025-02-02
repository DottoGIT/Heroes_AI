/*
 * File:        FogTile.cc
 * Description: Represents Fog of War tile
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        19.01.2025
 */

#include "FogTile.h"

void FogTile::setPosition(const Hex& position)
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
