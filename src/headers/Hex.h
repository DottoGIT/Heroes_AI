/*
 * File:        Hex.h
 * Description: Implements Hex offset coordinates "axial"
 *              Based on article Hexagonal Grids from Red Blob Games
 *              link: https://www.redblobgames.com/grids/hexagons/
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        05.11.2024
 */

#pragma once
#include <ostream>
#include <array>

struct Hex
{
    int q, r;
    Hex();
    Hex(int q, int r);
    int distanceTo(const Hex& other) const;
    bool operator==(const Hex& other) const;
    bool operator!=(const Hex& other) const;
    Hex operator+(const Hex& other) const;
    std::array<Hex, 6> neighbors() const;
    unsigned distance(const Hex& other) const;
    std::array<Hex, 9> neighborsSquare() const;
};

std::ostream& operator<<(std::ostream& os, const Hex& hex);