#include "RendersVisitator.h"
#include "BattleManager.h"
#include "MapManager.h"
#include "Logger.h"
#include "FieldUnit.h"
#include "MapTile.h"

void RendersVisitator::visitBattleManager(const BattleManager& battle_manager)
{
    objects_to_render_.clear();
    auto allUnits = battle_manager.getAllUnits();
    
    for(const std::shared_ptr<FieldUnit>& fieldUnit : allUnits)
    {
        objects_to_render_.push_back(fieldUnit);
    }
    background_ = battle_manager.getBackground();
    scene_type_ = SceneType::Battle;
    grid_dimensions_ = battle_manager.getBattleGridDimensions();
}

void RendersVisitator::visitMapManager(const MapManager& map_manager)
{
    map_manager.printMap();
    objects_to_render_.clear();
    for(const MapTile& tile : map_manager.getTiles())
    {
        //objects_to_render_.push_back(&tile);
    }
    scene_type_ = SceneType::Map;
    grid_dimensions_ = map_manager.getMapGridDimensions();
}