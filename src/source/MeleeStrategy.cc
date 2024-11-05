#include "MeleeStrategy.h"
#include "AttackType.h"

bool MeleeStrategy::canAttack(const Unit& attacker, const Unit& target) const
{
    return true;
}

void MeleeStrategy::attack(const Unit& attacker, const Unit& target) const
{

}

AttackType MeleeStrategy::getAttackType() const
{
    return AttackType::Melee;
}