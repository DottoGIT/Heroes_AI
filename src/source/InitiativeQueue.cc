#include "InitiativeQueue.h"
#include <algorithm>

InitiativeQueue::InitiativeQueue()
{}

InitiativeQueue::InitiativeQueue(const std::vector<std::shared_ptr<FieldUnit>> &units)
{ 
    std::vector<std::shared_ptr<FieldUnit>> sortedUnits = units;
    std::sort(sortedUnits.begin(), sortedUnits.end(), [](const std::shared_ptr<FieldUnit>& a, const std::shared_ptr<FieldUnit>& b) {
        return a->getInitiative() > b->getInitiative();
    });

    for (const auto& unit : sortedUnits) {
        unitsQueue_.push(unit);
    }
}

std::shared_ptr<FieldUnit> InitiativeQueue::popNextAndPush() {
    if (unitsQueue_.empty()) {
        return nullptr;
    }
    auto nextUnit = unitsQueue_.front();
    unitsQueue_.pop();
    unitsQueue_.push(nextUnit);
    return nextUnit;
}

std::vector<std::shared_ptr<FieldUnit>> InitiativeQueue::lookUpNextUnits(unsigned int number_of_units) const
{
    std::vector<std::shared_ptr<FieldUnit>> nextUnits;
    std::queue<std::shared_ptr<FieldUnit>> tempQueue = unitsQueue_;

    for (unsigned int i = 0; i < number_of_units; ++i) {
        std::shared_ptr<FieldUnit> popped = tempQueue.front();
        tempQueue.pop();
        tempQueue.push(popped);
        nextUnits.push_back(popped);
    }

    return nextUnits;
}