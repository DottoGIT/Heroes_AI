/*
 * File:        UnitMove.h
 * Description: Represents a move FieldUnit can make
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        27.12.2024
 */

#pragma once
#include "Hex.h"
#include "MoveType.h"

class UnitMove
{
public:
    UnitMove();
    static UnitMove move(const Hex& move_target);
    static UnitMove attack(const Hex& attack_target);
    static UnitMove wait();
    const MoveType getType() const;
    const Hex getTarget() const;
private:
    MoveType type_;
    Hex target_;
    UnitMove(const MoveType& type, const Hex& target);
};