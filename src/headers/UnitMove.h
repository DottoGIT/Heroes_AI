/*
 * File:        UnitMove.cc
 * Description: Represents a move FieldUnit can make
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        27.12.2024
 */

#pragma once
#include "Hex.h"

enum class MoveType {
    Wait,
    Move,
    Attack,
    MoveAndAttack
};

class UnitMove
{
private:
    MoveType type_;
    Hex move_target_;
    Hex attack_target_;
private:
    UnitMove(MoveType type, const Hex move_target, const Hex attack_target);
public:
    UnitMove();
    static UnitMove move(const Hex move_target);
    static UnitMove attack(const Hex attack_target);
    static UnitMove moveAndAttack(const Hex move_target, const Hex attack_target);
    const MoveType getType() const;
    const Hex getMoveTarget() const;
    const Hex getAttackTarget() const;
};