/*
 * File:        SymbolsToPaths.h
 * Description: Maps one letter symbols to existing sprite paths.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        03.01.2025
 */

#pragma once
#include <map>
#include <string>
#include <vector>

class SymbolsToPaths {
public:
    static std::map<char, std::string> symbols;
};

std::map<char, std::string> SymbolsToPaths::symbols{
    {'0', "media/map/ground.png"},
    {'1', "media/map/fog.png"}
};