/*
 * File:        MapManager.h
 * Description: Manages Map view.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */
#pragma once

#include <string>
#include <vector>
#include <memory>

#include "IManager.h"
#include "MapTile.h"
#include "MapDecoration.h"
#include "HexMap.hpp"
#include "MapHero.h"
#include "ResourceCounter.h"
#include "InputController.h"
#include "IClickable.h"
#include "MapPointer.h"
#include "FogTile.h"

class RendersVisitator;

constexpr int DISCOVERY_RADIUS = 5;

class MapManager : public IManager, public IClickable{
public:
    MapManager(std::weak_ptr<InputController> input_controller);
    ~MapManager();
    void printMap() const;
    const std::vector<MapTile>& getTiles() const;
    const std::vector<FogTile>& getFog() const;
    const std::vector<MapDecoration>& getDecorations() const;
    const MapHero* getHero() const;
    const MapPointer* getPointer() const;
    Hex getMapGridDimensions() const;
    void accept(RendersVisitator& visitor) const override;
    virtual void reactToClick(bool left_button, Hex click_position) override;
private:
    inline static const Hex PLAYER_START_POSITION = Hex(6,5);

    HexMap<MapTile> tiles_;
    HexMap<FogTile> fog_;
    std::vector<MapDecoration> decorations_;
    MapHero hero_;
    MapPointer pointer_;
    std::weak_ptr<InputController> input_controller_;
    MapTile* marked_tile_ = nullptr;

    void initFogOfWar(const Hex& point);
    void updateFogOfWar(const Hex& point);
    void moveHero(const Hex& point);
};