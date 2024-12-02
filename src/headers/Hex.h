#pragma once
#include <ostream>

struct Hex
{
    int q, r;
    Hex(int q, int r);

    bool operator==(const Hex& other) const;
};

std::ostream& operator<<(std::ostream& os, const Hex& hex);