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
#include "IRenderable.h"
#include "Hex.h"

class AttackStrategy;
enum class AttackType;
enum class ArmyType;

class FieldUnit : public Unit, public IRenderable
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
    ~FieldUnit() = default;
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
    ArmyType getArmyType() const;

    // IRenderable
    const std::string& getSpritePath() const override;
    int getSpritePriority() const override;
    Hex getSpriteDimensions() const override;
    Hex getPosition() const override;


private:
    std::unique_ptr<AttackStrategy> attack_strategy_;
    const std::string path_to_sprite_dead_;
    const unsigned int single_unit_health_;
    const unsigned int attack_strength_;
    const unsigned int walk_range_;
    const unsigned int initiative_;
    Hex position_;
    ArmyType army_;
};