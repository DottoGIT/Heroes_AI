/*
 * File:        Army.h
 * Description: Represents Player or AI forces.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#pragma once
#include <vector>
#include "Unit.h"

class Army
{
public:
    Army();
    void addUnit(Unit unit);
    const std::vector<Unit>& getUnits() const;
    Unit& at(const size_t index);
    std::vector<Unit>::const_iterator cbegin() const;
    std::vector<Unit>::const_iterator cend() const;
private:
    std::vector<Unit> units_;
};