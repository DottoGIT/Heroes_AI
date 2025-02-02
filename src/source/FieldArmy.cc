/*
 * File:        FieldArmy.cc
 * Description: Represents playable Player or AI forces on battle field.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        05.11.2024
 */

#include "FieldArmy.h"
#include "ArmyType.h"

constexpr size_t MAX_UNIT_COUNT = 7;

FieldArmy::FieldArmy()
{
    units_.reserve(MAX_UNIT_COUNT);
}

void FieldArmy::addUnit(const FieldUnit& unit)
{
    units_.push_back(std::move(unit));
}

const std::vector<FieldUnit>& FieldArmy::getUnits() const 
{
    return units_;
}

FieldUnit &FieldArmy::at(const size_t index)
{
    return units_.at(index);
}

std::vector<FieldUnit>::const_iterator FieldArmy::cbegin() const
{
    return units_.cbegin();
}

std::vector<FieldUnit>::const_iterator FieldArmy::cend() const
{
    return units_.cend();
}

std::vector<FieldUnit>::iterator FieldArmy::begin()
{
    return units_.begin();
}

std::vector<FieldUnit>::iterator FieldArmy::end()
{
    return units_.end();
}
