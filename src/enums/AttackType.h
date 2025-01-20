/*
 * File:        AttackType.h
 * Description: Identifies what attacks can Units have.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */
#pragma once

#include <ostream>

enum class AttackType {
    MELEE,
    RANGED
};

inline std::ostream& operator<<(std::ostream& os, AttackType type) {
    switch (type) {
        case AttackType::MELEE:
            os << "Melee";
            break;
        case AttackType::RANGED:
            os << "Ranged";
            break;
        default:
            os << "Unknown AttackType";
            break;
    }
    return os;
}