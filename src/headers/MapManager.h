/*
 * File:        MapManager.h
 * Description: Contains data about game map.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */
#pragma once

#include <string>

#include "IManager.h"
#include "MapTile.h"
#include "HexMap.hpp"

class RendersVisitator;

class MapManager : public IManager {
public:
    MapManager(const std::string& path);
    void printMap() const;
    const std::vector<MapTile>& getTiles() const;
    Hex getMapGridDimensions() const;
    void accept(RendersVisitator& visitor) const override;
private:
    HexMap<MapTile> tiles;
};