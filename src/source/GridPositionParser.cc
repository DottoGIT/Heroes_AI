/*
 * File:        PositionParser.cc
 * Description: Parses relative grid positions to wordspace renderer positions
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        17.12.2024
 */

#include "GridPositionParser.h"

Hex GridPositionParser::parseGridToPosition(const Hex& relative_pos, const Hex& cell_dimensions, const Hex& anchor_pos, const Hex& offset, int even_row_indent)
{
    return Hex(offset.q + anchor_pos.q + (relative_pos.q * cell_dimensions.q + ((relative_pos.r + 1) % 2) * even_row_indent), 
               offset.r + anchor_pos.r + (relative_pos.r * cell_dimensions.r));
}
Hex GridPositionParser::parsePositionToGrid(const Hex& screen_pos, const Hex& cell_dimensions, const Hex& anchor_pos, const Hex& offset, int even_row_indent)
{
    int q = screen_pos.q - anchor_pos.q - offset.q;
    int r = screen_pos.r - anchor_pos.r - offset.r;
    int relative_r = r / cell_dimensions.r;
    int relative_q = (q - ((relative_r + 1) % 2) * even_row_indent) / cell_dimensions.q;
    return Hex(relative_q, relative_r);
}

Hex GridPositionParser::axialToOddr(const Hex &hex)
{
    int col = hex.q + (hex.r - (hex.r&1)) / 2;
    int row = hex.r;
    return Hex(col, row);
}

Hex GridPositionParser::OddrToAxial(const Hex &hex)
{
    int q = hex.q - (hex.r - (hex.q&1)) / 2;
    int r = hex.r;
    return Hex(q, r);
}
