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
    ARCHER,
    ENCHANTER,
    SKELETON,
    SWORDSMAN
};

inline std::ostream& operator<<(std::ostream& os, UnitType type) {
    switch (type) {
        case UnitType::ARCHER:
            os << "Archer";
            break;
        case UnitType::ENCHANTER:
            os << "Enchanter";
            break;
        case UnitType::SKELETON:
            os << "Skeleton";
            break;
        case UnitType::SWORDSMAN:
            os << "Swordsman";
            break;
        default:
            os << "Unknown AttackType";
            break;
    }
    return os;
}