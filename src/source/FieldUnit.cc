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
      attack_strategy_(std::move(attack_strategy))
{
}

void FieldUnit::walkToCell() 
{ 

}

void FieldUnit::takeDamage() 
{ 

}

void FieldUnit::setArmy(const ArmyType& army)
{
    army_ = army;
}

void FieldUnit::setPosition(Hex hex)
{
    position_ = hex;
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
