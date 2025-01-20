/*
 * File:        UnitMove.h
 * Description: Represents a move FieldUnit can make
 *
 * Authors:     Wojciech Sarwiński <https://github.com/sarwoj>
 * 
 * Date:        27.12.2024
 */

#pragma once
#include <ostream>

enum class MoveType {
    WAIT,
    MOVE,
    ATTACK
};

inline std::ostream& operator<<(std::ostream& os, MoveType type) {
    switch (type) {
        case MoveType::WAIT:
            os << "Wait";
            break;
        case MoveType::MOVE:
            os << "Move";
            break;
        case MoveType::ATTACK:
            os << "Attack";
            break;
        default:
            os << "Unknown MoveType";
            break;
    }
    return os;
}
