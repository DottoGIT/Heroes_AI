/*
 * File:        InitiativeQueue.h
 * Description: Order in which units act in battle field
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <queue>
#include <vector>
#include <memory>
#include "FieldUnit.h"

class InitiativeQueue
{
public:
    InitiativeQueue(const std::vector<std::shared_ptr<FieldUnit>>& units);
    std::shared_ptr<FieldUnit> popNextAndPush();
    std::vector<std::shared_ptr<FieldUnit>> lookUpNextUnits(unsigned int number_of_units) const;
private:
    std::queue<std::shared_ptr<FieldUnit>> unitsQueue_;
};