#include "Unit.h"
#include "AttackStrategy.h"
#include "AttackType.h"
#include "UnitType.h"

Unit::Unit(const UnitType& type,
           const std::string& path_to_sprite_idle,
           unsigned int quantity)
    
    : type_(type),
      path_to_sprite_idle_(std::move(path_to_sprite_idle)),
      quantity_(quantity)
{ 
}

const UnitType& Unit::getType() const 
{ 
    return type_; 
}

unsigned int Unit::getQuantity() const 
{ 
    return quantity_; 
}