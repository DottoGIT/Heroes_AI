/*
 * File:        FieldUnitFactory.h
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

class FieldUnit;
enum class UnitType;

class FieldUnitFactory {
public:
    FieldUnitFactory();
    std::shared_ptr<FieldUnit> CreateUnit(const UnitType& type, unsigned int quantity = 1);

private:
    using UnitCreator = std::shared_ptr<FieldUnit>(FieldUnitFactory::*)(unsigned int);

    std::unordered_map<UnitType, UnitCreator> unit_creators_;

    void registerUnit(UnitType type, UnitCreator creator);

    // Units Creators
    std::shared_ptr<FieldUnit> createArcher(unsigned int quantity);
    std::shared_ptr<FieldUnit> createEnchanter(unsigned int quantity);
    std::shared_ptr<FieldUnit> createSkeleton(unsigned int quantity);
    std::shared_ptr<FieldUnit> createSwordsman(unsigned int quantity);
};
