#include "GridPositionParser.h"

Hex GridPositionParser::parse(const Hex& relative_pos, const Hex& cell_dimensions, const Hex& anchor_pos, const Hex& offset, int even_row_indent)
{
    return Hex(offset.q + anchor_pos.q + (relative_pos.q * cell_dimensions.q + ((relative_pos.r + 1) % 2) * even_row_indent), 
               offset.r + anchor_pos.r + (relative_pos.r * cell_dimensions.r));
}