#include <algorithm>
#include "Hex.h"

namespace {
        static const std::array<Hex, 6> neighbour_offsets = {
                Hex( 1, 0),
                Hex( 0, 1),
                Hex(-1, 1),
                Hex(-1, 0),
                Hex( 0,-1),
                Hex( 1,-1)
        };
};

Hex::Hex(int q, int r)
        : q(q), r(r) {}

Hex::Hex()
        : q(0), r(0) {}

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

std::ostream& operator<<(std::ostream& os, const Hex& hex) {
        os << "Hex(q: " << hex.q << ", r: " << hex.r << ")";
        return os;
}