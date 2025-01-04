#include "MapFileConverter.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Logger.h"

HexMap<MapTile> MapFileConverter::fileToMapConvertion()
{
    std::ifstream file(GROUND_PATH);
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


std::vector<MapDecoration> MapFileConverter::fileToDecorationsConvertion()
{
    std::ifstream file(DECORATIONS_PATH);
    if (!file.is_open())
    {
        Logger::error("Could Not Open Decorations File");
        throw std::runtime_error("Could not open decorations file!");
    }

    std::vector<MapDecoration> data;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        std::istringstream iss(line);
        char symbol;
        int pos_x, pos_y;

        if (!(iss >> symbol >> pos_x >> pos_y))
        {
            Logger::error("Invalid line format in decorations file: " + line);
            throw std::runtime_error("Invalid line format in decorations file!");
        }

        MapDecoration decoration;
        decoration.setSymbol(symbol);
        decoration.setPosition(Hex(pos_x, pos_y));
        data.push_back(decoration);
    }
    return data;
}



