/*
 * File:        RendersVisitator.h
 * Description: Visitator pattern, used by Display to gather render objects 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        02.12.2024
 */

#pragma once

#include <vector>
#include <memory>
#include "SDL2/SDL_image.h"
#include "IRenderable.h"
#include "SceneType.h"
#include "Hex.h"

class BattleManager;

class RendersVisitator
{
public:
    virtual ~RendersVisitator() = default;
    void visitBattleManager(const BattleManager& battle_manager);
protected:
    std::vector<std::shared_ptr<IRenderable>> objects_to_render_;
    Hex grid_dimensions_;
    std::string background_;
    SceneType scene_type_;
};
