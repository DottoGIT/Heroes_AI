#include "RendersVisitator.h"
#include "BattleManager.h"
#include "MapManager.h"
#include "Logger.h"

void RendersVisitator::visitBattleManager(const BattleManager& battle_manager)
{
    objects_to_render_.clear();
    
    for(const std::unique_ptr<FieldUnitRenderable>& fieldUnit : battle_manager.getAllUnits())
    {
        objects_to_render_.push_back(fieldUnit.get());
    }
    background_ = battle_manager.getBackground();
    scene_type_ = SceneType::Battle;
    grid_dimensions_ = battle_manager.getBattleGridDimensions();
}

void RendersVisitator::visitMapManager(const MapManager& map_manager)
{
    objects_to_render_.clear();
    decorations_to_render_.clear();
    for(const MapTile& tile : map_manager.getTiles())
    {
        objects_to_render_.push_back(&tile);
        auto interacable = tile.getConstInteractable();
        if(interacable)
        {
            decorations_to_render_.push_back(interacable);
        }
    }

    for(const MapDecoration& decorations : map_manager.getDecorations())
    {
        decorations_to_render_.push_back(&decorations);
    }

    for(const FogTile& fog : map_manager.getFog())
    {
        if(fog.isActive())
        {
            decorations_to_render_.push_back(&fog);
        }
    }

    decorations_to_render_.push_back(map_manager.getHero());
    decorations_to_render_.push_back(map_manager.getPointer());

    scene_type_ = SceneType::Map;
    grid_dimensions_ = map_manager.getMapGridDimensions();
}