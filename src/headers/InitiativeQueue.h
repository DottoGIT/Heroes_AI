/*
 * File:        InitiativeQueue.h
 * Description: Order in which units act in battle field
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        05.11.2024
 */

#pragma once
#include <vector>
#include <memory>
#include "FieldUnit.h"
#include "FieldArmy.h"

struct FieldUnitIndex
{
    ArmyType type;
    uint32_t index;
    FieldUnitIndex(const ArmyType& type, uint32_t index);
};

class InitiativeQueue
{
public:
    InitiativeQueue();
    InitiativeQueue(const FieldArmy& player, const FieldArmy& enemy);
    const FieldUnitIndex current() const;
    const FieldUnitIndex next();
    const std::vector<FieldUnitIndex>& getQueue() const;
private:
    std::vector<FieldUnitIndex> queue_;
};