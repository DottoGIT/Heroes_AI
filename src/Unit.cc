#include "Unit.h"
#include "AttackStrategy.h"
#include "AttackType.h"
#include "UnitType.h"

// Constructor implementation
Unit::Unit(const UnitType& type,
           const std::string& path_to_sprite_idle,
           const std::string& path_to_sprite_dead,
           unsigned int single_unit_health,
           unsigned int stack_health,
           unsigned int attack_strength,
           unsigned int walk_range,
           unsigned int initiative,
           std::unique_ptr<AttackStrategy> attack_strategy)
    
    : type_(type),
      path_to_sprite_idle_(std::move(path_to_sprite_idle)),
      path_to_sprite_dead_(std::move(path_to_sprite_dead)),
      single_unit_health_(single_unit_health),
      stack_health_(stack_health),
      attack_strength_(attack_strength),
      walk_range_(walk_range),
      initiative_(initiative),
      attack_strategy_(std::move(attack_strategy))
{ 
}

void Unit::walkToCell() 
{ 

}

void Unit::takeDamage() 
{ 

}

const UnitType& Unit::getType() const 
{ 
    return type_; 
}

const std::string& Unit::getPathToSpriteIdle() const 
{ 
    return path_to_sprite_idle_; 
}

const std::string& Unit::getPathToSpriteDead() const 
{ 
    return path_to_sprite_dead_; 
}

unsigned int Unit::getSingleUnitHealth() const 
{ 
    return single_unit_health_; 
}

unsigned int Unit::getStackHealth() const 
{ 
    return stack_health_; 
}

unsigned int Unit::getAttackStrength() const 
{ 
    return attack_strength_; 
}

unsigned int Unit::getWalkRange() const 
{ 
    return walk_range_; 
}

unsigned int Unit::getInitiative() const 
{ 
    return initiative_; 
}

AttackType Unit::getAttackType() const
{
    return attack_strategy_->getAttackType();
}

