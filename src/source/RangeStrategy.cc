#include "RangeStrategy.h"
#include "AttackType.h"

bool RangeStrategy::canAttack(const Unit& attacker, const Unit& target) const
{
    return true;
}

void RangeStrategy::attack(const Unit& attacker, const Unit& target) const
{

}

AttackType RangeStrategy::getAttackType() const
{
    return AttackType::Ranged;
}