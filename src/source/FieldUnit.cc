#include "Unit.h"
#include "FieldUnit.h"
#include "AttackStrategy.h"
#include "AttackType.h"
#include "ArmyType.h"

FieldUnit::FieldUnit(
                     const UnitType& type,
                     const std::string& path_to_sprite_idle,
                     unsigned int quantity,
                     const std::string& path_to_sprite_dead,
                     unsigned int single_unit_health,
                     unsigned int attack_strength,
                     unsigned int walk_range,
                     unsigned int initiative,
                     std::unique_ptr<AttackStrategy> attack_strategy)
    : Unit(type, std::move(path_to_sprite_idle), quantity),
      path_to_sprite_dead_(std::move(path_to_sprite_dead)),
      single_unit_health_(single_unit_health),
      attack_strength_(attack_strength),
      walk_range_(walk_range),
      initiative_(initiative),
      attack_strategy_(std::move(attack_strategy)),
      is_flipped_(false)
{ }

void FieldUnit::walkToCell() 
{ 

}

void FieldUnit::takeDamage() 
{ 

}

void FieldUnit::setArmy(const ArmyType& army)
{
    army_ = army;
    if(army == ArmyType::Computer) setFlip(true);
}

void FieldUnit::setPosition(Hex hex)
{
    position_ = hex;
}

void FieldUnit::setFlip(bool is_flipped)
{
    is_flipped_ = is_flipped;
}

const std::string& FieldUnit::getPathToSpriteDead() const 
{ 
    return path_to_sprite_dead_; 
}

unsigned int FieldUnit::getSingleUnitHealth() const 
{ 
    return single_unit_health_; 
}

unsigned int FieldUnit::getAttackStrength() const 
{ 
    return attack_strength_; 
}

unsigned int FieldUnit::getWalkRange() const 
{ 
    return walk_range_; 
}

unsigned int FieldUnit::getInitiative() const 
{ 
    return initiative_; 
}

AttackType FieldUnit::getAttackType() const
{
    return attack_strategy_->getAttackType();
}

Hex FieldUnit::getPosition() const
{
    return position_;
}

ArmyType FieldUnit::getArmyType() const
{
    return army_;
}

// IRenderable
const std::string& FieldUnit::getSpritePath() const
{
    return path_to_sprite_idle_;
}

int FieldUnit::getSpritePriority() const
{
    return OBJECT_PRIORTITY_1;
}

Hex FieldUnit::getSpriteDimensions() const
{
    return Hex(ONE_TILE_UNIT_WIDTH, ONE_TILE_UNIT_HEIGHT);
}


bool FieldUnit::isFlipped() const
{
    return is_flipped_;
}
