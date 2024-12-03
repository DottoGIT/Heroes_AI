#include "RendersVisitator.h"
#include "BattleManager.h"
#include "Logger.h"
#include "FieldUnit.h"

void RendersVisitator::visitBattleManager(const BattleManager& battle_manager)
{
    objects_to_render_.clear();
    auto allUnits = battle_manager.getAllUnits();
    
    for(const std::shared_ptr<FieldUnit>& fieldUnit : allUnits)
    {
        objects_to_render_.push_back(fieldUnit);
    }
    background_ = battle_manager.getBackground();
}