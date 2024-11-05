/*
 * File:        UnitFactory.h
 * Description: Creates new units
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
    std::unique_ptr<Unit> CreateUnit(const UnitType& type, unsigned int number_in_stack = 1);

private:
    using UnitCreator = std::unique_ptr<Unit>(UnitFactory::*)(unsigned int);

    std::unordered_map<UnitType, UnitCreator> unit_creators_;

    void registerUnit(UnitType type, UnitCreator creator);

    // Units Creators
    std::unique_ptr<Unit> createArcher(unsigned int number_in_stack);
    std::unique_ptr<Unit> createEnchanter(unsigned int number_in_stack);
    std::unique_ptr<Unit> createSkeleton(unsigned int number_in_stack);
    std::unique_ptr<Unit> createSwordsman(unsigned int number_in_stack);
};
