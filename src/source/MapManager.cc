#include "MapManager.h"
#include <sstream>
#include "RendersVisitator.h"
#include "MapFileConverter.h"
#include "Logger.h"
#include "GridPositionParser.h"
#include "Resource.h"

MapManager::MapManager(std::weak_ptr<InputController> input_controller)
    : tiles_(MapFileConverter::fileToMapConvertion()),
      fog_(HexMap<FogTile>(tiles_.getWidth()+1, tiles_.getHeight())),
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
    for (int j = 0; j < tiles_.getHeight(); ++j)
    {
        for (int i = 0; i < tiles_.getWidth(); ++i)
        {
            s << tiles_.at(Hex(i,j)).getSymbol() << " ";
        }
        s << "\n";
    }
    Logger::debug(s.str());
}

const std::vector<MapTile>& MapManager::getTiles() const
{
    return tiles_.getConstDataVector();
}

const std::vector<FogTile>& MapManager::getFog() const
{
    return fog_.getConstDataVector();
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
    return Hex(static_cast<int>(tiles_.getWidth()), static_cast<int>(tiles_.getHeight()));
}

void MapManager::reactToClick(bool left_button, Hex click_position)
{
    Hex pos = GridPositionParser::parsePositionToGrid(click_position, Hex(MAP_TILE_SIZE, MAP_TILE_SIZE), Hex(0,0), Hex(0,0), 0);
    
    if(pos.r >= tiles_.getHeight() || pos.q >= tiles_.getWidth())
    {
        return;
    }
    MapTile* clicked_tile = &tiles_.at(pos);
    if(!clicked_tile->isWalkable()) return;

    if(marked_tile_ != nullptr && marked_tile_->getPosition() == clicked_tile->getPosition())
    {
        moveHero(pos);
        updateFogOfWar(pos);
        clicked_tile->interact();
        pointer_.hide();
    }
    else
    {
        marked_tile_ = clicked_tile;
        pointer_.setPosition(pos);
    }
}

void MapManager::initFogOfWar(const Hex& point)
{
    for(int y = 0; y < fog_.getHeight(); y++)
    {
        for(int x = 0; x < fog_.getWidth(); x++)
        {
            fog_.at(Hex(x,y)).setPosition(Hex(x-1,y));
        }
    }
    updateFogOfWar(point);
}

void MapManager::updateFogOfWar(const Hex& point)
{
    for (int y = 0; y < fog_.getHeight(); y++)
    {
        for (int x = 0; x < fog_.getWidth(); x++)
        {
            Hex tile(x, y);
            if (point.distanceTo(tile) <= DISCOVERY_RADIUS)
            {
                fog_.at(tile).setActive(false);
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
