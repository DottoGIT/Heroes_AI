#include "FieldArmy.h"
#include "ArmyType.h"

FieldArmy::FieldArmy()
{}

FieldArmy::FieldArmy(const ArmyType &type)
{
    type_ = type; 
}

void FieldArmy::addUnit(std::shared_ptr<FieldUnit> unit)
{
    unit->setArmy(type_);
    units_.push_back(unit);
}

std::vector<std::shared_ptr<FieldUnit>> FieldArmy::getUnits() const 
{
    return units_;
}