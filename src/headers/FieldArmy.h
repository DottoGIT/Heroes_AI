/*
 * File:        FieldArmy.h
 * Description: Represents playable Player and AI forces on battle field.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <vector>
#include <memory>
#include "ArmyType.h"
#include "FieldUnit.h"

class FieldArmy
{
public:
    FieldArmy(const ArmyType& type);
    void addUnit(std::shared_ptr<FieldUnit> unit);
    std::vector<std::shared_ptr<FieldUnit>> getUnits() const;
private:
    std::vector<std::shared_ptr<FieldUnit>> units_;
    ArmyType type_;
};