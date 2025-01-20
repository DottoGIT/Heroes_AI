/*
 * File:        BattleManager.cc
 * Description: Sets up battle field, and manages battle flow.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */

#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

namespace {
    std::array<Hex, 7> player_start_positions = {
        Hex(0, 0),
        Hex(-1, 2),
        Hex(-2, 4),
        Hex(-3, 6),
        Hex(-4, 8),
        Hex(-5, 10),
        Hex(0, 1)
    };
};

namespace {
    std::array<Hex, 7> enemy_start_positions = {
        Hex(14, 0),
        Hex(13, 2),
        Hex(12, 4),
        Hex(11, 6),
        Hex(10, 8),
        Hex(9, 10),
        Hex(14, 1)
    };
};

BattleManager::BattleManager()
    : map_(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT), field_()
{}

BattleManager::BattleManager(const Army &player_army, const Army &enemy_army, HexMap<Tile> map)
    : map_(std::move(map))
{
    FieldArmy player_field_army;
    std::for_each(player_army.cbegin(), player_army.cend(),
    [&, index = 0](const Unit& unit) mutable {
        player_field_army.addUnit(FieldUnit(unit, player_start_positions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        index++;
    });
    FieldArmy enemy_field_army;
    std::for_each(enemy_army.cbegin(), enemy_army.cend(),
    [&, index = 0](const Unit& unit) mutable {
        enemy_field_army.addUnit(FieldUnit(unit, enemy_start_positions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        index++;
    });
    field_ = BattleField(std::move(player_field_army), std::move(enemy_field_army), &map_);
    background_ = "media/sprites/battlebg_green.png";
}

const BattleField &BattleManager::getBattleField() const
{
    return field_;
}

const std::string& BattleManager::getBackground() const
{
    return background_;
}

Hex BattleManager::getBattleGridDimensions() const
{
    return Hex(int(map_.getWidth()), int(map_.getHeight()));
}

const ArmyType BattleManager::getCurrentPlayer() const
{
    return field_.getQueue().current().type;
}

const FieldUnit &BattleManager::getCurrentUnit() const
{
    return field_.activeUnit();
}

const MoveType BattleManager::getCurrentMoveType() const
{
    return field_.getCurrentMoveType();
}

void BattleManager::makeMove(UnitMove unit_move)
{
    field_ = field_.makeMove(unit_move);
    std::vector<std::unique_ptr<FieldUnitRenderable>> units_to_render;
    for (const FieldUnit& unit : field_.getPlayer().getUnits())
    {
        units_to_render.emplace_back(std::make_unique<FieldUnitRenderable>(unit, texture_idle_.at(unit.getUnitType()), texture_dead_.at(unit.getUnitType()), ArmyType::PLAYER));
    }
    for (const FieldUnit& unit : field_.getEnemy().getUnits())
    {
        units_to_render.emplace_back(std::make_unique<FieldUnitRenderable>(unit, texture_idle_.at(unit.getUnitType()), texture_dead_.at(unit.getUnitType()), ArmyType::COMPUTER));
    }
    renderable_units_ = std::move(units_to_render);

}

const std::vector<std::unique_ptr<FieldUnitRenderable>> &BattleManager::getAllUnits() const
{
    return renderable_units_;
}

void BattleManager::accept(RendersVisitator& visitor) const
{
    visitor.visitBattleManager(*this);
}