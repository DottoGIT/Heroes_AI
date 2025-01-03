/*
 * File:        SymbolsToPaths.h
 * Description: Maps one letter symbols to existing sprite paths.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#pragma once
#include <map>
#include <string>
#include <vector>

class SymbolsToPaths {
public:
    static std::map<char, std::string> symbols;
};

std::map<char, std::string> SymbolsToPaths::symbols{
    {'0', "media/sprites/map/ground.png"},
    {'1', "media/sprites/map/fog.png"},
    {'2', "media/sprites/map/shore_t.png"},
    {'3', "media/sprites/map/sea.png"},
    {'4', "media/sprites/map/sea_corner.png"},
    {'5', "media/sprites/map/sea_corner_fill.png"},
    {'6', "media/sprites/map/gts.png"},
    {'7', "media/sprites/map/gts_corner.png"},
    {'8', "media/sprites/map/stg_corner.png"}
};