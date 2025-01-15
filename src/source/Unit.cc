#include "Unit.h"
#include "AttackStrategy.h"
#include "AttackType.h"
#include "UnitType.h"

Unit::Unit(
    const UnitType &type,
    unsigned int quantity, unsigned int single_unit_health,
    unsigned int attack_strength, unsigned int attack_range,
    unsigned int walk_range, unsigned int initiative
)   : type_(type),
    quantity_(quantity), single_unit_health_(single_unit_health),
    attack_strength_(attack_strength), attack_range_(attack_range),
    walk_range_(walk_range), initiative_(initiative)
{}

const UnitType &Unit::getType() const
{ 
    return type_; 
}

const Statistic& Unit::getQuantity() const 
{ 
    return quantity_; 
}

const Statistic& Unit::getSingleUnitHealth() const
{
    return single_unit_health_;
}

const Statistic& Unit::getAttackStrength() const
{
    return attack_strength_;
}

const Statistic& Unit::getAttackRange() const
{
    return attack_range_;
}

const Statistic& Unit::getWalkRange() const
{
    return walk_range_;
}

const Statistic& Unit::getInitiative() const
{
    return initiative_;
}

void Unit::increaseQuantity(unsigned int amount)
{
    quantity_.increase(amount);
}

void Unit::increaseSingleUnitHealth(unsigned int amount)
{
    single_unit_health_.increase(amount);
}

void Unit::increaseAttackStrength(unsigned int amount)
{
    attack_strength_.increase(amount);
}

void Unit::increaseAttackRange(unsigned int amount)
{
    attack_range_.increase(amount);
}

void Unit::increaseWalkRange(unsigned int amount)
{
    walk_range_.increase(amount);
}

void Unit::increaseInitiative(unsigned int amount)
{
    initiative_.increase(amount);
}
