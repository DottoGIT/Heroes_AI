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
#include <vector>

#include "IManager.h"
#include "MapTile.h"
#include "MapDecoration.h"
#include "HexMap.hpp"
#include "MapHero.h"
#include "ResourceCounter.h"

class RendersVisitator;

class MapManager : public IManager {
public:
    MapManager();
    void printMap() const;
    const std::vector<MapTile>& getTiles() const;
    const std::vector<MapDecoration>& getDecorations() const;
    const std::map<ResourceType, int>& getResources() const;
    const MapHero* getHero() const;
    Hex getMapGridDimensions() const;
    void accept(RendersVisitator& visitor) const override;
private:
    HexMap<MapTile> tiles_;
    std::vector<MapDecoration> decorations_;
    MapHero hero_;
    ResourceCounter resources_;
};