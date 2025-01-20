/*
 * File:        FieldUnit.cc
 * Description: Represents playable units on battle filed.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        05.11.2024
 */

#include "FieldUnit.h"

FieldUnit::FieldUnit(const Unit& unit, const Hex& position)
    : type_(unit.getType()), position_(position),
    health_(unit.getQuantity().get() * unit.getSingleUnitHealth().get()),
    attack_strength_(unit.getAttackStrength()), attack_range_(unit.getAttackRange()),
    walk_range_(unit.getWalkRange()), initiative_(unit.getInitiative())
{}

const UnitType &FieldUnit::getUnitType() const
{
    return type_;
}

const Hex &FieldUnit::getPosition() const
{
    return position_;
}

void FieldUnit::setPosition(const Hex& new_position)
{
    position_ = new_position;
}

const Health &FieldUnit::getHealth() const
{
    return health_;
}

void FieldUnit::takeDamage(unsigned int damage)
{
    health_.damage(damage);
}

const Statistic &FieldUnit::getAttackStrength() const
{
    return attack_strength_;
}

const Statistic &FieldUnit::getAttackRange() const
{
    return attack_range_;
}

const Statistic &FieldUnit::getWalkRange() const
{
    return walk_range_;
}

const Statistic &FieldUnit::getInitiative() const
{
    return initiative_;
}