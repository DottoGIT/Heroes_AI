/*
 * File:        BattleManager.cc
 * Description: Sets up battle field, and manages battle flow.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 *              Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        05.11.2024
 */

#include "BattleManager.h"
#include "RendersVisitator.h"
#include "Logger.h"
#include "GridPositionParser.h"
#include "UnitType.h"

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

    std::array<Hex, 7> enemy_start_positions = {
        Hex(14, 0),
        Hex(13, 2),
        Hex(12, 4),
        Hex(11, 6),
        Hex(10, 8),
        Hex(9, 10),
        Hex(14, 1)
    };

    constexpr int BATTLE_GRID_ANCHOR_X = 0;
    constexpr int BATTLE_GRID_ANCHOR_Y = 100;
    constexpr int BATTLE_GRID_CELL_SIZE = 52;
    constexpr int BATTLE_GRID_CELL_HEIGHT = 39; // Hex rows size, smaller than size (prefferable 3/4)
    constexpr int BATTLE_GRID_EVEN_ROW_INDENT = 26; // prefferable (1/2)
    constexpr int BATTLE_OFFSET_X = 5;
    constexpr int BATTLE_OFFSET_Y = -60;
};

BattleManager::BattleManager()
    : map_(BATTLE_HEX_WIDTH, BATTLE_HEX_HEIGHT), field_(), selected_(std::nullopt), computer_move_future_(std::nullopt), winner_(ArmyType::NONE)
{}

BattleManager::BattleManager(const Army &player_army, const Army &enemy_army, HexMap<Tile> map, std::weak_ptr<InputController> input_controller, std::function<void()> change_mode_function)
    : map_(std::move(map)), change_mode_function_(change_mode_function), input_controller_(input_controller), selected_(std::nullopt), computer_move_future_(std::nullopt), winner_(ArmyType::NONE)
{
    FieldArmy player_field_army;
    std::for_each(player_army.cbegin(), player_army.cend(),
    [&, index = 0](const Unit& unit) mutable {
        player_field_army.addUnit(FieldUnit(unit, player_start_positions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        ++index;
    });
    FieldArmy enemy_field_army;
    std::for_each(enemy_army.cbegin(), enemy_army.cend(),
    [&, index = 0](const Unit& unit) mutable {
        enemy_field_army.addUnit(FieldUnit(unit, enemy_start_positions.at(index)));
        texture_idle_[unit.getType()] = unit.getPathIdle();
        texture_dead_[unit.getType()] = unit.getPathDead();
        ++index;
    });
    field_ = BattleField(std::move(player_field_army), std::move(enemy_field_army), &map_);
    afterMove();
    background_ = "media/sprites/battlebg_green.png";
    if(auto locked = input_controller_.lock())
    {
        locked->subscribeToMouseClick(this);
    }
    else
    {
        Logger::warning("Input Manager destroyed before BattleFieldManager");
        throw std::runtime_error("Input Manager destroyed before BattleFieldManager");
    }
    minmax_ = MinMax(field_);
    std::stringstream ss;
    ss << "Initialized new BattleManager with " << field_.getPlayer().getUnits().size();
    ss << " player units and " << field_.getEnemy().getUnits().size() << " enemy units";
    Logger::info(ss.str());
}

BattleManager::~BattleManager()
{
    if(auto locked = input_controller_.lock())
    {
        locked->unsubscribeFromMouseClick(this);
    }
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

void BattleManager::makeMove(const UnitMove& unit_move)
{
    std::stringstream ss;
    ss << getCurrentPlayer() << " move: ";
    ss << getCurrentUnit().getUnitType() << " " << unit_move.getType();
    if (unit_move.getType() != MoveType::WAIT) {
            ss << " target " << unit_move.getTarget();
    }
    Logger::info(ss.str());
    field_ = field_.makeMove(unit_move);
    afterMove();
}

const std::vector<std::unique_ptr<FieldUnitRenderable>> &BattleManager::getAllUnits() const
{
    return renderable_units_;
}

void BattleManager::accept(RendersVisitator& visitor) const
{
    visitor.visitBattleManager(*this);
}

void BattleManager::reactToClick(bool left_button, const Hex &click_position)
{
    Hex hex = GridPositionParser::parsePositionToHex(
        click_position,
        Hex(BATTLE_GRID_CELL_SIZE, BATTLE_GRID_CELL_HEIGHT),
        Hex(BATTLE_GRID_ANCHOR_X, BATTLE_GRID_ANCHOR_Y),
        BATTLE_GRID_EVEN_ROW_INDENT
    );
    if (getCurrentPlayer() == ArmyType::COMPUTER) return;
    if (selected_ && *selected_ == hex) {
        if (selected_ == getCurrentUnitPos()) {
            makeMove(UnitMove::wait());
        } else if (field_.getCurrentMoveType() == MoveType::ATTACK) {
            makeMove(UnitMove::attack(hex));
        } else {
            makeMove(UnitMove::move(hex));
        }
    } else {
        selectTile(hex);
    }
}

const std::vector<std::unique_ptr<GridTile>> &BattleManager::getAllMoves() const
{
    if (selected_)
    {
        return path_tiles_;
    }
    return move_tiles_;
}

void BattleManager::tryMakeComputerMove()
{
    if (computer_move_future_ && computer_move_future_->wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        std::stringstream ss;
        ss << "Computer move ready.";
        ss << " Positions checked: " << minmax_.getPositionsCheckedCount();
        ss << " Transposition table hits: " << minmax_.getTranspositionTableHits();
        Logger::info(ss.str());
        UnitMove computer_move = computer_move_future_->get();
        computer_move_future_.reset();
        makeMove(computer_move);
    }
}

void BattleManager::tryPromiseComputerMove()
{
    if (getCurrentPlayer() != ArmyType::COMPUTER)
        return;
    Logger::info("Starting MinMax on new thread.");
    computer_move_future_ = std::async(
        std::launch::async,
        [this]()
        {
            return minmax_.minMax(field_, COMPUTER_DEPTH_SEARCH);
        }
    );
}

void BattleManager::makeGridTiles()
{
    std::vector<std::unique_ptr<GridTile>> new_grid_tiles;
    for (const UnitMove& move : current_moves_)
    {
        new_grid_tiles.emplace_back(std::make_unique<GridTile>(move.getTarget()));
    }
    move_tiles_ = std::move(new_grid_tiles);
}

void BattleManager::makeRenderable()
{
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

void BattleManager::afterMove()
{
    selected_ = std::nullopt;
    winner_ = field_.whoWon();
    getMoves();
    makeRenderable();
    makeGridTiles();
    tryOnWin();
    tryPromiseComputerMove();
}

void BattleManager::getMoves()
{
    current_moves_ = field_.getMoves();
    current_moves_.at(0) = UnitMove(MoveType::WAIT, getCurrentUnitPos());
}

void BattleManager::selectTile(const Hex &select_hex)
{
    if (std::find_if(current_moves_.cbegin(), current_moves_.cend(),[&](const UnitMove& move){return move.getTarget() == select_hex;}) == current_moves_.cend())
    {
        selected_ = std::nullopt;
        return;
    }
    selected_ = select_hex;
    if (field_.getCurrentMoveType() == MoveType::MOVE)
    {
        selected_path_ = field_.getPath(select_hex);
        std::vector<std::unique_ptr<GridTile>> new_path;
        for (const Hex& move : selected_path_)
        {
            new_path.emplace_back(std::make_unique<GridTile>(move));
        }
        path_tiles_ = std::move(new_path);
    } else {
        selected_path_ = {};
        std::vector<std::unique_ptr<GridTile>> new_path;
        new_path.emplace_back(std::make_unique<GridTile>(select_hex));
        path_tiles_ = std::move(new_path);
    }
}

const Hex BattleManager::getCurrentUnitPos() const
{
    return field_.activeUnit().getPosition();
}

void BattleManager::tryOnWin()
{
    if (winner_ == ArmyType::NONE)
        return;
    std::stringstream ss;
    ss << "Game ended with " << winner_ << " victory.";
    Logger::info(ss.str());
    change_mode_function_();
}