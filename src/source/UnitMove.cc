#include "UnitMove.h"

UnitMove::UnitMove()
    : type_(MoveType::Wait)
{}

UnitMove::UnitMove(MoveType type, const Hex move_target, const Hex attack_target)
    : type_(type), move_target_(move_target), attack_target_(attack_target)
{}

UnitMove UnitMove::move(const Hex move_target)
{
    return UnitMove(MoveType::Move, move_target, Hex());
}

UnitMove UnitMove::attack(const Hex attack_target)
{
    return UnitMove(MoveType::Attack, Hex(), attack_target);
}

UnitMove UnitMove::moveAndAttack(const Hex move_target, const Hex attack_target)
{
    return UnitMove(MoveType::MoveAndAttack, move_target, attack_target);
}

const MoveType UnitMove::getType() const
{
    return type_;
}

const Hex UnitMove::getMoveTarget() const
{
    return move_target_;
}

const Hex UnitMove::getAttackTarget() const
{
    return attack_target_;
}
