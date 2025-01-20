#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"

namespace {
    std::array<Hex, 7> playerStartPositions = {
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
    std::array<Hex, 7> enemyStartPositions = {
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

BattleManager::BattleManager(const Army &playerArmy, const Army &enemyArmy, HexMap<Tile> map)
    : map_(std::move(map))
{
    FieldArmy playerFieldArmy;
    std::for_each(playerArmy.cbegin(), playerArmy.cend(),
    [&, index = 0](const Unit& unit) mutable {
        playerFieldArmy.addUnit(FieldUnit(unit, playerStartPositions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        index++;
    });
    FieldArmy enemyFieldArmy;
    std::for_each(enemyArmy.cbegin(), enemyArmy.cend(),
    [&, index = 0](const Unit& unit) mutable {
        enemyFieldArmy.addUnit(FieldUnit(unit, enemyStartPositions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        index++;
    });
    field_ = BattleField(std::move(playerFieldArmy), std::move(enemyFieldArmy), &map_);
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

void BattleManager::MakeMove(UnitMove unitMove)
{
    field_ = field_.makeMove(unitMove);
    std::vector<std::unique_ptr<FieldUnitRenderable>> units_to_render;
    for (const FieldUnit& unit : field_.getPlayer().getUnits())
    {
        units_to_render.push_back(std::make_unique<FieldUnitRenderable>(unit, texture_idle_.at(unit.getUnitType()), texture_dead_.at(unit.getUnitType())));
    }
    for (const FieldUnit& unit : field_.getEnemy().getUnits())
    {
        units_to_render.push_back(std::make_unique<FieldUnitRenderable>(unit, texture_idle_.at(unit.getUnitType()), texture_dead_.at(unit.getUnitType())));
    }
    renderable_units_ = units_to_render;

}

const std::vector<std::unique_ptr<FieldUnitRenderable>> &BattleManager::getAllUnits() const
{
    return renderable_units_;
}

void BattleManager::accept(RendersVisitator& visitor) const
{
    visitor.visitBattleManager(*this);
}