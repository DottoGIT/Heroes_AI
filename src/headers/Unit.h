/*
 * File:        Unit.h
 * Description: Universal class for every unit in the game.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */

#pragma once

#include <string>

class AttackStrategy;
enum class UnitType;

class Unit {
public:    
    Unit(
        const UnitType& type,
        const std::string& path_to_sprite_idle,
        unsigned int quantity);
    virtual ~Unit() = default;
    
    const UnitType& getType() const;
    const std::string& getPathToSpriteIdle() const;
    unsigned int getQuantity() const;

private:
    const UnitType type_;
    const std::string path_to_sprite_idle_;
    unsigned int quantity_;
};
