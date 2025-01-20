/*
 * File:        MapManager.cc
 * Description: Manages Map view.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#include "MapManager.h"
#include <sstream>
#include "RendersVisitator.h"
#include "MapFileConverter.h"
#include "Logger.h"
#include "GridPositionParser.h"
#include "Resource.h"

MapManager::MapManager(std::weak_ptr<InputController> input_controller)
    : tiles_(MapFileConverter::fileToMapConvertion()),
      decorations_(MapFileConverter::fileToDecorationsConvertion()),
      input_controller_(input_controller)
{
    hero_.setPosition(PLAYER_START_POSITION);
    initFogOfWar(PLAYER_START_POSITION);
    if(auto locked = input_controller_.lock())
    {
        locked->subscribeToMouseClick(this);
    }
    else
    {
        Logger::warning("Input Manager destroyed before MapManager");
    }
}

MapManager::~MapManager()
{
    if(auto locked = input_controller_.lock())
    {
        locked->unsubscribeFromMouseClick(this);
    }
    else
    {
        Logger::warning("Input Manager destroyed before MapManager");
    }
}

void MapManager::accept(RendersVisitator& visitor) const
{
    visitor.visitMapManager(*this);
}

void MapManager::printMap() const
{
    std::stringstream s;
    s << "\n";
    for (int j = 0; j < MAP_HEIGHT; ++j)
    {
        for (int i = 0; i < MAP_WIDTH; ++i)
        {
            s << tiles_[i][j].getSymbol() << " ";
        }
        s << "\n";
    }
    Logger::debug(s.str());
}

std::vector<const MapTile*> MapManager::getTiles() const
{
    std::vector<const MapTile*> tiles_vector;

    for (int j = 0; j < MAP_HEIGHT; ++j)
    {
        for (int i = 0; i < MAP_WIDTH; ++i)
        {
            tiles_vector.push_back(&tiles_[i][j]);
        }
    }
    return tiles_vector;
}

std::vector<const FogTile*> MapManager::getFog() const
{    
    std::vector<const FogTile*> fog_vector;

    for (int j = 0; j < MAP_HEIGHT; ++j)
    {
        for (int i = 0; i < MAP_WIDTH+1; ++i)
        {
            fog_vector.push_back(&fog_[i][j]);
        }
    }
    return fog_vector;
}

const std::vector<MapDecoration>& MapManager::getDecorations() const
{
    return decorations_;
}

const MapHero* MapManager::getHero() const
{
    return &hero_;
}

const MapPointer* MapManager::getPointer() const
{
    return &pointer_;
}

Hex MapManager::getMapGridDimensions() const
{
    return Hex(MAP_WIDTH, MAP_HEIGHT);
}

void MapManager::reactToClick(bool left_button, Hex click_position)
{
    Hex pos = GridPositionParser::parsePositionToGrid(click_position, Hex(MAP_TILE_SIZE, MAP_TILE_SIZE), Hex(0,0), Hex(0,0), 0);
    
    if(pos.r >= MAP_HEIGHT || pos.q >= MAP_WIDTH)
    {
        return;
    }

    MapTile* clicked_tile = &tiles_[pos.q][pos.r];
    if(!clicked_tile->isWalkable()) return;

    if(marked_tile_ != nullptr && marked_tile_->getPosition() == clicked_tile->getPosition())
    {
        moveHero(pos);
        updateFogOfWar(pos);
        interactWithTile(pos);
        pointer_.hide();
    }
    else
    {
        marked_tile_ = clicked_tile;
        pointer_.setPosition(pos, isTileOccupiedByUnit(pos));
    }
}

void MapManager::initFogOfWar(const Hex& point)
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH+1; x++)
        {
            fog_[x][y].setPosition(Hex(x-1,y));
        }
    }
    updateFogOfWar(point);
}

void MapManager::updateFogOfWar(const Hex& point)
{
    for (int y = 0;  y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH+1; x++)
        {
            Hex tile(x, y);
            if (point.distanceTo(tile) <= DISCOVERY_RADIUS)
            {
                fog_[x][y].setActive(false);
            }
        }
    }
}

void MapManager::moveHero(const Hex& point)
{
    Hex hero_offset = Hex(point.q, point.r-1);
    hero_.setFlip(hero_offset.q < hero_.getPosition().q);
    hero_.setPosition(hero_offset);
}

MapEnemy* MapManager::isTileOccupiedByUnit(const Hex& point)
{
    Hex unitOffset = Hex(point.q, point.r-1);
    std::array<Hex, 9> neighbours = unitOffset.neighborsSquare();

    for(const auto& n : neighbours)
    {
        if(n.q < 0 || n.r < 0 || n.q >= MAP_WIDTH || n.r >= MAP_HEIGHT) continue;
        MapTile tile = tiles_[n.q][n.r];
        if(tile.getInteractable() && tile.getInteractable()->myObjectType() == MapObjectType::Enemy)
        {

            MapEnemy* enemy = dynamic_cast<MapEnemy*>(tile.getInteractable());
            return enemy;
        }
    }
    return nullptr;
}

void MapManager::interactWithTile(const Hex& point)
{
    MapEnemy* foundEnemy = isTileOccupiedByUnit(point);
    if(!foundEnemy)
    {
        tiles_[point.q][point.r].interact();
        return;
    }

    foundEnemy->interact();
}

