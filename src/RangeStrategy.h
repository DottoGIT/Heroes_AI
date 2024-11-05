/*
 * File:        RangeStrategy.h
 * Description: Defines Range Strategy class for AttackStrategy Pattern 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include "AttackStrategy.h"

enum class AttackType;

class RangeStrategy : public AttackStrategy
{
public:
    virtual ~RangeStrategy() = default;
    virtual bool canAttack(const Unit& attacker, const Unit& target) const;
    virtual void attack(const Unit& attacker, const Unit& target) const;
    virtual AttackType getAttackType() const;
};