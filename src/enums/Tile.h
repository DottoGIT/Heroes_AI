/*
 * File:        Tile.h
 * Description: Identifies types of tiles on map.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        28.11.2024
 */

#pragma once
#include <ostream>

enum class Tile {
    REACHABLE,
    UNREACHABLE
};

inline std::ostream& operator<<(std::ostream& os, Tile type) {
    switch (type) {
        case Tile::REACHABLE:
            os << "Reachable";
            break;
        case Tile::UNREACHABLE:
            os << "Unreachable";
            break;
        default:
            os << "Unknown SceneType";
            break;
    }
    return os;
}