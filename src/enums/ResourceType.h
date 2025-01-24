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
            os << "Ruda";
            break;
        case ResourceType::MERCURY:
            os << "Rtec";
            break;
        case ResourceType::SULFUR:
            os << "Siarka";
            break;
        case ResourceType::WOOD:
            os << "Drewno";
            break;
        case ResourceType::GEMS:
            os << "Klejnoty";
            break;
        case ResourceType::GOLD:
            os << "Zloto";
            break;
        case ResourceType::CRYSTALS:
            os << "Krysztaly";
            break;
        default:
            os << "Unknown ResourceType";
            break;
    }
    return os;
}