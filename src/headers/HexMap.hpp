#pragma once
#include <vector>
#include <array>
#include <iterator>
#include <stdexcept>

#include "Hex.h"

template <typename T>
class HexMap {
private:
    std::size_t width_, height_;
    std::vector<T> data_;
public:
    HexMap(std::size_t width, std::size_t height);
    T& at(Hex hex);
    bool inBounds(Hex hex) const;
    std::vector<Hex> getNeighbors(Hex hex) const;

    struct Iterator {
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = value_type*;
            using reference = value_type&;
        private:
            HexMap* map;
            std::size_t index;
        public:
            Iterator(HexMap* map, std::size_t index) : map(map), index(index) {}

            reference operator*() const;
            Iterator& operator++();
            bool operator!=(const Iterator &other) const;

            Hex coords() const;
    };
    Iterator begin() { return Iterator(this, 0); }
    Iterator end() { return Iterator(this, data_.size()); }

private:
    std::size_t hexToIndex(Hex hex) const noexcept;
};

template <typename T>
HexMap<T>::HexMap(std::size_t width, std::size_t height)
    : width_(width), height_(height), data_(width * height)
{}

template <typename T>
T& HexMap<T>::at(Hex hex)
{
    if (!in_bounds(hex))
        throw std::out_of_range("Column or row out of range!");
    std::size_t index = hexToIndex(hex);
    
    return data_[index];
}

template <typename T>
bool HexMap<T>::inBounds(Hex hex) const
{
    if (hex.r < 0 || hex.r >= height_)
        return false;
    int q_min = -hex.r / 2;
    int q_max = width_ - 1 + q_min;
    return (hex.q >= q_min && hex.q <= q_max);
}

template <typename T>
inline std::vector<Hex> HexMap<T>::getNeighbors(Hex hex) const
{
    std::vector<Hex> neighbors;

    static const std::array<std::pair<int, int>, 6> neighbor_offsets = {{
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
        {1, -1},
        {-1, 1}
    }};

    for (const auto& offset : neighbor_offsets) {
        Hex neighbor(hex.q + offset.first, hex.r + offset.second);
        if (in_bounds(neighbor)) {
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

template <typename T>
std::size_t HexMap<T>::hexToIndex(Hex hex) const noexcept
{
    int r_offset = hex.r / 2;
    int q_adjusted = hex.q + r_offset;
    return hex.r * width_ + q_adjusted;
}

template <typename T>
inline typename HexMap<T>::Iterator::reference HexMap<T>::Iterator::operator*() const
{
    return map->data_[index];
}

template <typename T>
inline typename HexMap<T>::Iterator& HexMap<T>::Iterator::operator++()
{
    ++index;
    return *this;
}

template <typename T>
inline bool HexMap<T>::Iterator::operator!=(const Iterator &other) const
{
    return index != other.index;
}

template <typename T>
inline Hex HexMap<T>::Iterator::coords() const
{
    int r = index / map->width_;
    int q = index % map->width_ - (r / 2);
    return Hex(q, r);
}
