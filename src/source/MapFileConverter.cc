/*
 * File:        MapFileConverter.cc
 * Description: Handles convertion between map objects and files.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#include <vector>
#include <fstream>
#include <sstream>
#include "MapFileConverter.h"
#include "SymbolsTranslator.h"
#include "Logger.h"

std::array<std::array<MapTile, CONVERTER_MAP_HEIGHT>, CONVERTER_MAP_WIDTH> MapFileConverter::fileToMapConvertion()
{
    std::array<std::array<MapTile, CONVERTER_MAP_HEIGHT>, CONVERTER_MAP_WIDTH> map;
    std::ifstream file_ground(GROUND_PATH);
    std::ifstream file_interactable(INTERACTABLE_PATH);
    std::ifstream file_walkable(WALKABLE_PATH);
    if (!file_ground.is_open() || 
        !file_interactable.is_open() ||
        !file_walkable.is_open())
    {
        Logger::error("Could Not Open Map Files");
        throw std::runtime_error("Could Not Open Map Files!");
    }
    std::string line_ground;
    std::string line_interactable;
    std::string line_walkable;
    size_t width = 0;
    int pos_y = 0;
    
    while (std::getline(file_ground, line_ground) && 
           std::getline(file_interactable, line_interactable) &&
           std::getline(file_walkable, line_walkable)) 
    {
        if (line_ground.empty() || line_interactable.empty() || line_walkable.empty()) 
        {
            Logger::warning("Empty Line Detected Inside Map File");
            continue;
        }

        if (width == 0) 
        {
            width = line_ground.size();
        }

        if ((line_ground.size() != line_interactable.size()) ||
            (line_ground.size() != line_walkable.size())) 
        {
            Logger::error("Mismatch in line length between map files.");
            continue; 
        }

        for(int i = 0; i < line_ground.length(); ++i)
        {
            MapTile tile;
            tile.setSymbol(line_ground[i]);
            tile.setPosition(Hex(i, pos_y));
            tile.setWalkable(line_walkable[i] == '0');

            if(SymbolsTranslator::symbolsToObjects[line_interactable[i]])
            {
                auto resource_form_file = SymbolsTranslator::symbolsToObjects[line_interactable[i]]->clone();
                std::string sprite_path = SymbolsTranslator::symbolsToPaths[line_interactable[i]];
                resource_form_file->setSpritePath(sprite_path);
                tile.setInteractable(resource_form_file);
            }
            map[i][pos_y] = tile;
        }

        ++pos_y;
    }
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



