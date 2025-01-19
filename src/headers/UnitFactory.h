/*
 * File:        UnitFactory.h
 * Description: Creates new units on battle field
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <memory>
#include <unordered_map>
#include <string>

class Unit;
enum class UnitType;

class UnitFactory {
public:
    UnitFactory();
    Unit CreateUnit(const UnitType& type, unsigned int quantity = 1);

private:
    using UnitCreator = Unit(UnitFactory::*)(unsigned int);

    std::unordered_map<UnitType, UnitCreator> unit_creators_;

    void registerUnit(UnitType type, UnitCreator creator);

    // Units Creators
    Unit createArcher(unsigned int quantity);
    Unit createEnchanter(unsigned int quantity);
    Unit createSkeleton(unsigned int quantity);
    Unit createSwordsman(unsigned int quantity);
};
