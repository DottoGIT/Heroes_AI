#include "RendersVisitator.h"
#include "BattleManager.h"
#include "Logger.h"
#include "RenderObject.h"
#include "FieldUnit.h"

void RendersVisitator::visitBattleManager(const BattleManager& battle_manager)
{
    objects_to_render_.clear();
    auto allUnits = battle_manager.getAllUnits();
    
    for(const std::shared_ptr<FieldUnit>& fieldUnit : allUnits)
    {
        RenderObject renderObject;
        renderObject.priority = fieldUnit->getPriority();
        renderObject.path = fieldUnit->getPath();
        objects_to_render_.push_back(renderObject);
    }
    background_ = battle_manager.getBackground();
}