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
#include <functional>
#include "IManager.h"
#include "MapTile.h"
#include "MapDecoration.h"
#include "MapHero.h"
#include "ResourceCounter.h"
#include "InputController.h"
#include "IClickable.h"
#include "MapPointer.h"
#include "FogTile.h"
#include "MapEnemy.h"

class RendersVisitator;

constexpr int DISCOVERY_RADIUS = 5;
constexpr int MAP_WIDTH = 25;
constexpr int MAP_HEIGHT = 18;

class MapManager : public IManager, public IClickable{
public:
    MapManager(std::weak_ptr<InputController> input_controller, std::function<void(const Army&, const Hex&)> change_mode_function);
    ~MapManager();
    void printMap() const;
    std::vector<const MapTile*> getTiles() const;
    std::vector<const FogTile*> getFog() const;
    const std::vector<MapDecoration>& getDecorations() const;
    const MapHero* getHero() const;
    const MapPointer* getPointer() const;
    Hex getMapGridDimensions() const;
    void accept(RendersVisitator& visitor) const override;
    void removeEnemy(const Hex& position);
    virtual void reactToClick(bool left_button, const Hex& click_position) override;
private:
    inline static const Hex PLAYER_START_POSITION = Hex(6,5);
    std::function<void(const Army&, const Hex&)> change_mode_function_;
    std::array<std::array<MapTile, MAP_HEIGHT>, MAP_WIDTH> tiles_;
    std::array<std::array<FogTile, MAP_HEIGHT>, MAP_WIDTH+1> fog_;
    std::vector<MapDecoration> decorations_;
    MapHero hero_;
    MapPointer pointer_;
    std::weak_ptr<InputController> input_controller_;
    MapTile* marked_tile_ = nullptr;
    void initFogOfWar(const Hex& point);
    void updateFogOfWar(const Hex& point);
    void moveHero(const Hex& point);
    MapEnemy* isTileOccupiedByUnit(const Hex& point);
    void interactWithTile(const Hex& point);
};