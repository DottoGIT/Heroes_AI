#include "MapManager.h"
#include "RendersVisitator.h"
#include "MapFileConverter.h"
#include "Logger.h"
#include <sstream>

MapManager::MapManager(const std::string& path)
    : tiles(MapFileConverter::fileToMapConvertion(path))
{}

void MapManager::accept(RendersVisitator& visitor) const
{
    visitor.visitMapManager(*this);
}

void MapManager::printMap() const
{
    std::stringstream s;
    s << "\n";
    for (int j = 0; j < tiles.getHeight(); ++j) 
    {
        for (int i = 0; i < tiles.getWidth(); ++i) 
        {
                s << tiles.at(Hex(i,j)).getSymbol() << " ";
        }
        s << "\n";
    }
    Logger::debug(s.str());
}

const std::vector<MapTile>& MapManager::getTiles() const
{
    return tiles.getDataVector();
}

Hex MapManager::getMapGridDimensions() const
{
    return Hex(static_cast<int>(tiles.getWidth()), static_cast<int>(tiles.getHeight()));
}