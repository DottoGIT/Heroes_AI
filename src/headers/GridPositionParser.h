/*
 * File:        PositionParser.h
 * Description: Parses relative grid positions to wordspace renderer positions
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        17.12.2024
 */
#pragma once
#include "Hex.h"

class GridPositionParser
{
public:
    static Hex GridPositionParser::parseGridToPosition(const Hex& relative_pos, const Hex& cell_dimensions, const Hex& anchor_pos, const Hex& offset, int even_row_indent);
    static Hex GridPositionParser::parsePositionToGrid(const Hex& screen_pos, const Hex& cell_dimensions, const Hex& anchor_pos, const Hex& offset, int even_row_indent);
};