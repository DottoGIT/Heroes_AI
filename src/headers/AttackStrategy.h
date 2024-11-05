/*
 * File:        AttackStrategy.h
 * Description: Implementation of Strategy Pattern, used for different 
 *              attack types in units such as range or melee.
 * 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */
#pragma once
#include <string>
#include <memory>

class Unit;
enum class AttackType;

class AttackStrategy{
public:
    virtual ~AttackStrategy() = default;
    virtual bool canAttack(const Unit& attacker, const Unit& target) const = 0;
    virtual void attack(const Unit& attacker, const Unit& target) const = 0;
    virtual AttackType getAttackType() const = 0;
};