#include "MapManager.h"
#include <sstream>
#include "RendersVisitator.h"
#include "MapFileConverter.h"
#include "Logger.h"

MapManager::MapManager()
    : tiles_(MapFileConverter::fileToMapConvertion()),
      decorations_(MapFileConverter::fileToDecorationsConvertion())
{
    hero_.setPosition(Hex(6, 5));
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
    return tiles_.getDataVector();
}

const std::vector<MapDecoration>& MapManager::getDecorations() const
{
    return decorations_;
}

const MapHero* MapManager::getHero() const
{
    return &hero_;
}

Hex MapManager::getMapGridDimensions() const
{
    return Hex(static_cast<int>(tiles_.getWidth()), static_cast<int>(tiles_.getHeight()));
}