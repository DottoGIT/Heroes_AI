/*
 * File:        BattleManager.h
 * Description: Sets up battle field, and manages battle flow.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 *              Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */

#pragma once
#include <queue>
#include <memory>
#include <vector>
#include <optional>
#include <future>
#include "BattleField.h"
#include "Army.h"
#include "Hex.h"
#include "IManager.h"
#include "HexMap.hpp"
#include "FieldUnitRenderable.h"
#include "IClickable.h"
#include "InputController.h"
#include "GridTile.h"
#include "MinMax.h"

class RendersVisitator;

constexpr unsigned int BATTLE_HEX_WIDTH = 15;
constexpr unsigned int BATTLE_HEX_HEIGHT = 11;
constexpr int COMPUTER_DEPTH_SEARCH = 6;

class BattleManager  : public IManager, public IClickable
{
public:
    BattleManager();
    BattleManager(const Army& player_army, const Army& enemy_army, HexMap<Tile> map, std::weak_ptr<InputController> input_controller, std::function<void()> change_mode_function);
    virtual ~BattleManager();
    const BattleField& getBattleField() const;
    const std::string& getBackground() const;
    Hex getBattleGridDimensions() const;
    const ArmyType getCurrentPlayer() const;
    const FieldUnit& getCurrentUnit() const;
    const MoveType getCurrentMoveType() const;
    void makeMove(const UnitMove& unitMove);
    const std::vector<std::unique_ptr<FieldUnitRenderable>>& getAllUnits() const;
    void accept(RendersVisitator& visitor) const override;
    virtual void reactToClick(bool left_button, const Hex& click_position);
    const std::vector<std::unique_ptr<GridTile>>& getAllMoves() const;
    void tryMakeComputerMove();
private:
    void tryPromiseComputerMove();
    void makeGridTiles();
    void makeRenderable();
    void afterMove();
    void getMoves();
    void selectTile(const Hex& select_hex);
    const Hex getCurrentUnitPos() const;
    void tryOnWin();
private:
    BattleField field_;
    HexMap<Tile> map_;
    std::string background_;
    MinMax minmax_;
    std::vector<std::unique_ptr<FieldUnitRenderable>> renderable_units_;
    std::unordered_map<UnitType, std::string> texture_idle_;
    std::unordered_map<UnitType, std::string> texture_dead_;
    std::vector<UnitMove> current_moves_;
    std::vector<std::unique_ptr<GridTile>> move_tiles_;
    std::vector<std::unique_ptr<GridTile>> path_tiles_;
    std::vector<Hex> selected_path_;
    std::optional<Hex> selected_;
    std::optional<std::future<UnitMove>> computer_move_future_;
    ArmyType winner_;


    std::weak_ptr<InputController> input_controller_;
    std::function<void()> change_mode_function_;
};