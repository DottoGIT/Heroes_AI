/*
 * File:        Army.cc
 * Description: Represents Player or AI forces.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#include "Army.h"

Army::Army()
{}

void Army::addUnit(const Unit& unit)
{
    units_.emplace_back(unit);
}

const std::vector<Unit> &Army::getUnits() const
{
    return units_;
}

Unit &Army::at(size_t index)
{
    return units_.at(index);
}

std::vector<Unit>::const_iterator Army::cbegin() const
{
    return units_.cbegin();
}

std::vector<Unit>::const_iterator Army::cend() const
{
    return units_.cend();
}
