/*
 * File:        Unit.h
 * Description: Represents playable units in battle filed.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <string>
#include <memory>

#include "Unit.h"
#include "Hex.h"

class AttackStrategy;
enum class AttackType;
enum class ArmyType;

class FieldUnit : public Unit
{
public:
    FieldUnit(
         const UnitType& type,
         const std::string& path_to_sprite_idle,
         unsigned int quantity,
         const std::string& path_to_sprite_dead,
         unsigned int single_unit_health,
         unsigned int attack_strength,
         unsigned int walk_range,
         unsigned int initiative,
         std::unique_ptr<AttackStrategy> attack_strategy);
    
    void walkToCell();
    void takeDamage();

    void setArmy(const ArmyType& army);
    void setPosition(Hex hex);

    const std::string& getPathToSpriteDead() const;
    unsigned int getSingleUnitHealth() const;
    unsigned int getAttackStrength() const;
    unsigned int getWalkRange() const;
    unsigned int getInitiative() const;
    AttackType getAttackType() const;
    Hex getPosition() const;
    ArmyType getArmyType() const;

private:
    std::unique_ptr<AttackStrategy> attack_strategy_;
    const std::string path_to_sprite_dead_;
    const unsigned int single_unit_health_;
    const unsigned int attack_strength_;
    const unsigned int walk_range_;
    const unsigned int initiative_;
    Hex position_ = Hex(0, 0);
    ArmyType army_;
};