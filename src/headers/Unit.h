/*
 * File:        Unit.h
 * Description: Class for every unit in the game outside battle.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        04.11.2024
 */

#pragma once
#include <string>
#include "Statistic.h"

enum class UnitType;

class Unit {
public:    
    Unit(
        const UnitType& type,
        unsigned int quantity, unsigned int single_unit_health,
        unsigned int attack_strength, unsigned int attack_range,
        unsigned int walk_range, unsigned int initiative,
        std::string path_to_idle, std::string path_to_dead
        );
    const UnitType& getType() const;
    const Statistic& getQuantity() const;
    const Statistic& getSingleUnitHealth() const;
    const Statistic& getAttackStrength() const;
    const Statistic& getAttackRange() const;
    const Statistic& getWalkRange() const;
    const Statistic& getInitiative() const;
    const std::string& getPathIdle() const;
    const std::string& getPathDead() const;
    void increaseQuantity(unsigned int amount);
    void increaseSingleUnitHealth(unsigned int amount);
    void increaseAttackStrength(unsigned int amount);
    void increaseAttackRange(unsigned int amount);
    void increaseWalkRange(unsigned int amount);
    void increaseInitiative(unsigned int amount);
private:
    const UnitType type_;
    Statistic quantity_;
    Statistic single_unit_health_;
    Statistic attack_strength_;
    Statistic attack_range_;
    Statistic walk_range_;
    Statistic initiative_;
    std::string texture_idle_;
    std::string texture_dead_;
};
