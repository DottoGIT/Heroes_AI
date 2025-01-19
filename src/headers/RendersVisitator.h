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
#include "ResourceCounter.h"

class BattleManager;
class MapManager;

class RendersVisitator
{
public:
    virtual ~RendersVisitator() = default;
    void visitBattleManager(const BattleManager& battle_manager);
    void visitMapManager(const MapManager& map_manager);
protected:
    std::vector<const IRenderable*> objects_to_render_;
    std::vector<const IRenderable*> decorations_to_render_;
    Hex grid_dimensions_;
    std::string background_;
    SceneType scene_type_;
    std::map<ResourceType, int> resources;
};
