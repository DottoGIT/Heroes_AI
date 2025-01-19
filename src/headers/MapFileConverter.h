/*
 * File:        MapFileConverter.h
 * Description: Handles convertion between map objects and files.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */
#pragma once

#include <string.h>
#include "HexMap.hpp"
#include "MapTile.h"
#include "MapDecoration.h"

constexpr const char* GROUND_PATH = "data/ground.txt";
constexpr const char* DECORATIONS_PATH = "data/decorations.txt";
constexpr const char* INTERACTABLE_PATH = "data/interactable.txt";
constexpr const char* WALKABLE_PATH = "data/walkable.txt";

class MapFileConverter {
public:
    HexMap<MapTile> static fileToMapConvertion();
    std::vector<MapDecoration> static fileToDecorationsConvertion();
};