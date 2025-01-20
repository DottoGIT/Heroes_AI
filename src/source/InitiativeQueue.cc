/*
 * File:        InitiativeQueue.cc
 * Description: Order in which units act in battle field
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 *              Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        05.11.2024
 */

#include <algorithm>
#include "InitiativeQueue.h"

FieldUnitIndex::FieldUnitIndex(const ArmyType& pType, uint32_t pIndex)
    : type(pType), index(pIndex)
{}

InitiativeQueue::InitiativeQueue()
{}

InitiativeQueue::InitiativeQueue(const FieldArmy &player, const FieldArmy &enemy)
{
    queue_.reserve(player.getUnits().size() + enemy.getUnits().size());
    int index = 0;
    for (const FieldUnit& unit : player.getUnits())
    {
        queue_.emplace_back(ArmyType::PLAYER, index);
        ++index;
    }
    index = 0;
    for (const FieldUnit& unit : enemy.getUnits())
    {
        queue_.emplace_back(ArmyType::COMPUTER, index);
        ++index;
    }
    std::sort(
        queue_.begin(), queue_.end(),
        [&](const FieldUnitIndex& a, const FieldUnitIndex& b) {
            Statistic initiative_a = (a.type == ArmyType::PLAYER) ?
                player.getUnits().at(a.index).getInitiative() : enemy.getUnits().at(a.index).getInitiative();
            Statistic initiative_b = (b.type == ArmyType::PLAYER) ?
                player.getUnits().at(b.index).getInitiative() : enemy.getUnits().at(b.index).getInitiative();
            return initiative_a > initiative_b;
        });
}

const FieldUnitIndex InitiativeQueue::current() const
{
    return queue_.front();
}

const FieldUnitIndex InitiativeQueue::next()
{
    if (queue_.size() < 2) return queue_.front();
    std::rotate(queue_.begin(), queue_.begin() + 1, queue_.end());
    return queue_.front();
}

const std::vector<FieldUnitIndex> &InitiativeQueue::getQueue() const
{
    return queue_;
}
