/*
 * File:        MapObjectType.h
 * Description: Identifies types of interactables objects on map.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        19.01.2024
 */

#pragma once
#include <ostream>

enum class MapObjectType {
    RESOURCE,
    ENEMY
};

inline std::ostream& operator<<(std::ostream& os, MapObjectType type) {
    switch (type) {
        case MapObjectType::RESOURCE:
            os << "Resource";
            break;
        case MapObjectType::ENEMY:
            os << "Enemy";
            break;
        default:
            os << "Unknown MapObjectType";
            break;
    }
    return os;
}
