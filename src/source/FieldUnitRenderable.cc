#include "FieldUnitRenderable.h"
#include "UnitType.h"

FieldUnitRenderable::FieldUnitRenderable(FieldUnit unit, std::string path_to_idle, std::string path_to_dead, ArmyType army)
    : position_(unit.getPosition()), alive_(unit.getHealth().isAlive()), path_to_idle_(path_to_idle), path_to_dead_(path_to_dead), flipped_(army == ArmyType::Computer)
{}

const std::string &FieldUnitRenderable::getSpritePath() const
{
    if (alive_)
        return path_to_idle_;
    return path_to_dead_;
}

Hex FieldUnitRenderable::getSpriteDimensions() const
{
    return Hex(ONE_TILE_UNIT_WIDTH, ONE_TILE_UNIT_HEIGHT);
}

int FieldUnitRenderable::getSpritePriority() const
{
    return OBJECT_PRIORTITY_1;
}

Hex FieldUnitRenderable::getPosition() const
{
    return position_;
}

bool FieldUnitRenderable::isFlipped() const
{
    return flipped_;
}
