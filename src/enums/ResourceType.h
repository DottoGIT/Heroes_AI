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
    Coal,
    Mercury,
    Sulfur,
    Wood,
    Gems,
    Gold,
    Crystals
};

inline std::ostream& operator<<(std::ostream& os, ResourceType type) {
    switch (type) {
        case ResourceType::Coal:
            os << "Coal";
            break;
        case ResourceType::Mercury:
            os << "Mercury";
            break;
        case ResourceType::Sulfur:
            os << "Sulfur";
            break;
        case ResourceType::Wood:
            os << "Wood";
            break;
        case ResourceType::Gems:
            os << "Gems";
            break;
        case ResourceType::Gold:
            os << "Gold";
            break;
        case ResourceType::Crystals:
            os << "Crystals";
            break;
        default:
            os << "Unknown ResourceType";
            break;
    }
    return os;
}