#include <algorithm>
#include <limits>
#include "MinMax.h"
#include "BattleField.h"

MinMax::MinMax(const BattleField &battlefield)
{}

int MinMax::evaluate(const BattleField &battlefield) const
{
    ArmyType is_winner = battlefield.whoWon();
    if (is_winner == ArmyType::COMPUTER)
        return std::numeric_limits<int>::min();
    if (is_winner == ArmyType::PLAYER)
        return std::numeric_limits<int>::max();
    
    int enemy_strength = 0;
    for (const FieldUnit& unit : battlefield.getEnemy().getUnits())
        enemy_strength += unit.getAttackStrength().get() * unit.getHealth().get();
    int player_strength = 0;
    for (const FieldUnit& unit : battlefield.getPlayer().getUnits())
        player_strength += unit.getAttackStrength().get() * unit.getHealth().get();
    
    return player_strength - enemy_strength;
}

std::pair<BattleField, int> MinMax::minMax(BattleField battlefield, int depth, int alpha, int beta)
{
    if (depth == 0 || battlefield.whoWon() != ArmyType::NONE) {
        return {battlefield, evaluate(battlefield)};
    }

    BattleField best_move;
    int best_score;
    if (battlefield.getQueue().current().type == ArmyType::PLAYER) {

        best_score = std::numeric_limits<int>::min();
        std::vector<UnitMove> moves = battlefield.getMoves();

        for (const UnitMove& move : moves)
        {
            BattleField newBattlefield = battlefield.makeMove(move);
            std::pair<BattleField, int> score = minMax(std::move(battlefield), depth - 1, alpha, beta);
            if (score.second > best_score)
            {
                best_move = std::move(score.first);
                best_score = score.second;
            }
            alpha = std::max(alpha, best_score);
            if (beta <= alpha)
                break;
        }
    }
    else
    {
        best_score = std::numeric_limits<int>::max();
        std::vector<UnitMove> moves = battlefield.getMoves();

        for (const UnitMove& move : moves)
        {
            BattleField newBattlefield = battlefield.makeMove(move);
            std::pair<BattleField, int> score = minMax(std::move(battlefield), depth - 1, alpha, beta);
            if (score.second < best_score)
            {
                best_move = std::move(score.first);
                best_score = score.second;
            }
            beta = std::min(beta, best_score);
            if (beta <= alpha)
                break;
        }
    }

    return {best_move, best_score};
}
