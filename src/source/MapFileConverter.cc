#include "MapFileConverter.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Logger.h"

HexMap<MapTile> MapFileConverter::fileToMapConvertion(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        Logger::error("Could Not Open File Map");
        throw std::runtime_error("Could not open file!");
    }

    std::vector<MapTile> data;
    std::string line;
    size_t width = 0;
    int pos_y = 0;
    int pos_x = 0;
    
    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;

        if (width == 0) 
        {
            width = line.size();
        }

        for (char c : line) 
        {
            MapTile tile;
            tile.setSymbol(c);
            tile.setPosition(Hex(pos_x, pos_y));
            data.push_back(tile);
            ++pos_x;
        }
        ++pos_y;
        pos_x = 0;
    }
    
    size_t height = data.size() / width;
    HexMap<MapTile> map(width, height);
    map.setData(data);

    return map;
}

