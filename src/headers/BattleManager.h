/*
 * File:        BattleManager.h
 * Description: Sets up battle field, and manages battle flow.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */

#pragma once
#include <queue>
#include <memory>
#include <vector>
#include "BattleField.h"
#include "Army.h"
#include "Hex.h"
#include "IManager.h"
#include "HexMap.hpp"
#include "FieldUnitRenderable.h"

class RendersVisitator;

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;

class BattleManager : public IManager
{
public:
    BattleManager();
    BattleManager(const Army& player_army, const Army& enemy_army, HexMap<Tile> map);
    const BattleField& getBattleField() const;
    const std::string& getBackground() const;
    Hex getBattleGridDimensions() const;
    const ArmyType getCurrentPlayer() const;
    const FieldUnit& getCurrentUnit() const;
    const MoveType getCurrentMoveType() const;
    void makeMove(UnitMove unitMove);
    const std::vector<std::unique_ptr<FieldUnitRenderable>>& getAllUnits() const;
    void accept(RendersVisitator& visitor) const override;
private:
    BattleField field_;
    HexMap<Tile> map_;
    std::string background_;
    std::vector<std::unique_ptr<FieldUnitRenderable>> renderable_units_;
    std::unordered_map<UnitType, std::string> texture_idle_;
    std::unordered_map<UnitType, std::string> texture_dead_;
};