/*
 * File:        FieldUnit.h
 * Description: Represents playable units on battle filed.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <string>
#include <memory>

#include "Unit.h"
#include "Health.h"
#include "Hex.h"

class FieldUnit
{
public:
    FieldUnit(const Unit& unit, Hex position);
    const UnitType& getUnitType() const;
    const Hex& getPosition() const;
    void setPosition(Hex new_position);
    const Health& getHealth() const;
    void takeDamage(unsigned int damage);
    const Statistic& getAttackStrength() const;
    const Statistic& getAttackRange() const;
    const Statistic& getWalkRange() const;
    const Statistic& getInitiative() const;

private:
    const UnitType type_;
    Hex position_;
    Health health_;
    const Statistic attack_strength_;
    const Statistic attack_range_;
    const Statistic walk_range_;
    const Statistic initiative_;
};