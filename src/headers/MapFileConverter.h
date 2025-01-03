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

class MapFileConverter {
public:
    HexMap<MapTile> static fileToMapConvertion(const std::string& path);
};