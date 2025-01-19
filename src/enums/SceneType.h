/*
 * File:        SceneType.h
 * Description: Used by Display to specify style of rendered scene
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        17.12.2024
 */
#pragma once

#include <ostream>

enum class SceneType
{
    Battle,
    Map
};

inline std::ostream& operator<<(std::ostream& os, SceneType type) {
    switch (type) {
        case SceneType::Battle:
            os << "Battle";
            break;
        case SceneType::Map:
            os << "Map";
            break;
        default:
            os << "Unknown SceneType";
            break;
    }
    return os;
}
