/*
 * File:        Hex.cc
 * Description: Implements Hex offset coordinates "axial"
 *              Based on article Hexagonal Grids from Red Blob Games
 *              link: https://www.redblobgames.com/grids/hexagons/
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        05.11.2024
 */

#include "Hex.h"
#include <algorithm>

namespace {
        static const std::array<Hex, 6> neighbour_offsets = {
                Hex( 1, 0),
                Hex( 0, 1),
                Hex(-1, 1),
                Hex(-1, 0),
                Hex( 0,-1),
                Hex( 1,-1)
        };
        static const std::array<Hex, 9> neighbour_offsets_square = {
                Hex(-1, -1),
                Hex(0, -1),
                Hex(1, -1),
                Hex(1, 0),
                Hex(1, 1),
                Hex(0, 1),
                Hex(-1, 1),
                Hex(-1, 0),
                Hex(0, 0)
        };
};

Hex::Hex(int q, int r)
        : q(q), r(r) {}

Hex::Hex()
        : q(0), r(0) {}


int Hex::distanceTo(const Hex& other) const
{
        return int(sqrt(pow(other.q - q, 2) + pow(other.r - r, 2)));
}

bool Hex::operator==(const Hex& other) const {
        return q == other.q && r == other.r;
}

bool Hex::operator!=(const Hex &other) const
{
    return q != other.q || r != other.r;
}

Hex Hex::operator+(const Hex &other) const
{
    return Hex(q + other.q, r + other.r);
}

std::array<Hex, 6> Hex::neighbors() const
{
    std::array<Hex, 6> results;
    std::transform(
        neighbour_offsets.begin(), neighbour_offsets.end(), results.begin(),
        [this](const Hex& hex_offset){
                return *this + hex_offset;
        });
    return results;
}

unsigned Hex::distance(const Hex &other) const
{
    return (abs(q - other.q)
          + abs(q + r - other.q - other.r)
          + abs(r - other.r)) / 2;
}

std::array<Hex, 9> Hex::neighborsSquare() const
{
    std::array<Hex, 9> offsets = neighbour_offsets_square;
    std::array<Hex, 9> results;
    std::transform(
        offsets.begin(), offsets.end(), results.begin(),
        [this](const Hex& hex_offset){
                return *this + hex_offset;
        });
    return results;
}

std::ostream& operator<<(std::ostream& os, const Hex& hex) {
        os << "Hex(q: " << hex.q << ", r: " << hex.r << ")";
        return os;
}