/*
 * File:        Unit.h
 * Description: Universal class for every playable unit in the game.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */

#pragma once

#include <string>
#include <memory>

class AttackStrategy;
enum class AttackType;
enum class UnitType;

class Unit {
public:    
    Unit(const UnitType& type,
         const std::string& path_to_sprite_idle,
         const std::string& path_to_sprite_dead,
         unsigned int single_unit_health,
         unsigned int stack_health,
         unsigned int attack_strength,
         unsigned int walk_range,
         unsigned int initiative,
         std::unique_ptr<AttackStrategy> attack_strategy);
    virtual ~Unit() = default;

    // Funcionality
    void walkToCell();
    void takeDamage();

    // Getters
    const UnitType& getType() const;
    const std::string& getPathToSpriteIdle() const;
    const std::string& getPathToSpriteDead() const;
    unsigned int getSingleUnitHealth() const;
    unsigned int getStackHealth() const;
    unsigned int getAttackStrength() const;
    unsigned int getWalkRange() const;
    unsigned int getInitiative() const;
    AttackType getAttackType() const;

private:
    std::unique_ptr<AttackStrategy> attack_strategy_;
    const UnitType type_;
    const std::string path_to_sprite_idle_;
    const std::string path_to_sprite_dead_;
    const unsigned int single_unit_health_;
    const unsigned int attack_strength_;
    const unsigned int walk_range_;
    const unsigned int initiative_;

    unsigned int stack_health_;
};
