#pragma once
#include <ostream>

struct Hex
{
    int q, r;
    Hex(int q, int r)
        : q(q), r(r) {}
    
    // Boost need this operator to perform tests (e.g unit.pos == hex(1,2))
    bool operator==(const Hex& other) const {
        return q == other.q && r == other.r;
    }
    friend std::ostream& operator<<(std::ostream& os, const Hex& hex) {
        os << "Hex(q: " << hex.q << ", r: " << hex.r << ")";
        return os;
    }
};