#include "GridTile.h"

namespace 
{
    const std::string GRID_TILE_PATH = "media/sprites/grid_marker.png";
    constexpr int GRID_TILE_WIDTH = 48;
    constexpr int GRID_TILE_HEIGHT = 96;
    constexpr int GRID_TILE_PRIORITY = 0;
}

GridTile::GridTile(const Hex &position)
    : position_(position)
{}

const std::string &GridTile::getSpritePath() const {
    return GRID_TILE_PATH;
}

Hex GridTile::getSpriteDimensions() const
{
    return Hex(GRID_TILE_WIDTH, GRID_TILE_HEIGHT);
}

int GridTile::getSpritePriority() const
{
    return GRID_TILE_PRIORITY;
}

Hex GridTile::getPosition() const
{
    return position_;
}

bool GridTile::isFlipped() const
{
    return false;
}
