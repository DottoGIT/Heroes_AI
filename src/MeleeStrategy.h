/*
 * File:        MeleeStrategy.h
 * Description: Defines Melee Strategy class for AttackStrategy Pattern 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */
#pragma once

#include "AttackStrategy.h"

enum class AttackType;

class MeleeStrategy : public AttackStrategy
{
public:
    virtual ~MeleeStrategy() = default;

    virtual bool canAttack(const Unit& attacker, const Unit& target) const;
    virtual void attack(const Unit& attacker, const Unit& target) const;
    virtual AttackType getAttackType() const;
};