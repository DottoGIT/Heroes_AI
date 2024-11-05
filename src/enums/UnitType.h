/*
 * File:        UnitType.h
 * Description: Identifies what Units are in the game.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */

#pragma once

#include <ostream>

enum class UnitType {
    Archer,
    Enchanter,
    Skeleton,
    Swordsman
};

inline std::ostream& operator<<(std::ostream& os, UnitType type) {
    switch (type) {
        case UnitType::Archer:
            os << "Archer";
            break;
        case UnitType::Enchanter:
            os << "Enchanter";
            break;
        case UnitType::Skeleton:
            os << "Skeleton";
            break;
        case UnitType::Swordsman:
            os << "Swordsman";
            break;
        default:
            os << "Unknown AttackType";
            break;
    }
    return os;
}