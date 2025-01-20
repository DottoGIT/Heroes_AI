/*
 * File:        ResourceType.h
 * Description: Identifies types of collectable resources.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.11.2024
 */

#pragma once
#include <ostream>

enum class ResourceType {
    COAL,
    MERCURY,
    SULFUR,
    WOOD,
    GEMS,
    GOLD,
    CRYSTALS
};

inline std::ostream& operator<<(std::ostream& os, ResourceType type) {
    switch (type) {
        case ResourceType::COAL:
            os << "Coal";
            break;
        case ResourceType::MERCURY:
            os << "Mercury";
            break;
        case ResourceType::SULFUR:
            os << "Sulfur";
            break;
        case ResourceType::WOOD:
            os << "Wood";
            break;
        case ResourceType::GEMS:
            os << "Gems";
            break;
        case ResourceType::GOLD:
            os << "Gold";
            break;
        case ResourceType::CRYSTALS:
            os << "Crystals";
            break;
        default:
            os << "Unknown ResourceType";
            break;
    }
    return os;
}