#include <Hex.h>

Hex::Hex(int q, int r)
        : q(q), r(r) {}

bool Hex::operator==(const Hex& other) const {
        return q == other.q && r == other.r;
}

std::ostream& operator<<(std::ostream& os, const Hex& hex) {
        os << "Hex(q: " << hex.q << ", r: " << hex.r << ")";
        return os;
}