/*
 * File:        UnitMove.cc
 * Description: Represents a move FieldUnit can make
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        27.12.2024
 */

#include "UnitMove.h"

UnitMove::UnitMove()
    : type_(MoveType::Wait)
{}

UnitMove::UnitMove(MoveType type, const Hex target)
    : type_(type), target_(target)
{}

UnitMove UnitMove::move(const Hex move_target)
{
    return UnitMove(MoveType::Move, move_target);
}

UnitMove UnitMove::attack(const Hex attack_target)
{
    return UnitMove(MoveType::Attack, attack_target);
}

UnitMove UnitMove::wait()
{
    return UnitMove(MoveType::Wait, Hex());
}

const MoveType UnitMove::getType() const
{
    return type_;
}

const Hex UnitMove::getTarget() const
{
    return target_;
}
