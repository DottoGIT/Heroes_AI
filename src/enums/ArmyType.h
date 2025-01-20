/*
 * File:        ArmyType.h
 * Description: Specifies if an unit is from player Army or AI army
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */
#pragma once

#include <ostream>

enum class ArmyType
{
    Player,
    Computer
};

inline std::ostream& operator<<(std::ostream& os, ArmyType type) {
    switch (type) {
        case ArmyType::Player:
            os << "Player";
            break;
        case ArmyType::Computer:
            os << "Computer";
            break;
        default:
            os << "Unknown ArmyType";
            break;
    }
    return os;
}