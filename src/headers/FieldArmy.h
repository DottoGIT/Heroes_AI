/*
 * File:        FieldArmy.h
 * Description: Represents playable Player or AI forces on battle field.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwinski <https://github.com/sarwoj>
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
    FieldArmy();
    void addUnit(FieldUnit unit);
    const std::vector<FieldUnit>& getUnits() const;
    FieldUnit& at(const size_t index);
    std::vector<FieldUnit>::const_iterator cbegin() const;
    std::vector<FieldUnit>::const_iterator cend() const;
    std::vector<FieldUnit>::iterator begin();
    std::vector<FieldUnit>::iterator end();
private:
    std::vector<FieldUnit> units_;
};