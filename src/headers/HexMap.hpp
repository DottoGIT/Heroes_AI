#pragma once
#include <vector>
#include <array>
#include <iterator>
#include <stdexcept>
#include <queue>
#include <functional>

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
    std::vector<Hex> findPath(Hex start, Hex end, const std::function<bool(Hex)>& reachable);
    std::vector<Hex> findPath(Hex start, Hex end, const std::function<bool(Hex)>& reachable, unsigned distance);
    HexMap<bool> getReachableTiles(Hex start, std::function<bool(Hex)>& reachable, unsigned distance);

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
std::vector<Hex> HexMap<T>::getNeighbors(Hex hex) const
{
    std::vector<Hex> neighbors;

    for (Hex neighbour : hex.neighbors()) {
        if (in_bounds(neighbor)) {
            neighbors.push_back(neighbor);
        }
    }
    return neighbors;
}

template <typename T>
inline std::vector<Hex> HexMap<T>::findPath(Hex start, Hex end, const std::function<bool(Hex)>& reachable)
{
    if (!reachable(end)) return {};

    HexMap<Hex> previous(width_, height_);
    HexMap<bool> visited(width_, height_);
    std::fill(visited.begin(), visited.end(), false);

    previous.at(start) = start;

    std::queue<Hex> queue;
    queue.push(start);
    while (!queue.empty())
    {
        Hex current = queue.front();
        queue.pop();
        visited.at(current) = true;

        if (current == end) {
            std::vector<Hex> path;
            for (Hex step = end; step != start; step = previous.at(step)) path.push_back(step);
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Hex neighbour : getNeighbors(current)) {
            if (visited.at(neighbour) || reachable(neighbour)) continue;
            queue.push(neighbour);
            previous.at(neighbour) = current;
        }
    }
    return {};
}

template <typename T>
inline std::vector<Hex> HexMap<T>::findPath(Hex start, Hex end, const std::function<bool(Hex)>& reachable, unsigned distance)
{
    if (!reachable(end) || distance == 0) return {};

    HexMap<Hex> previous(width_, height_);
    HexMap<bool> visited(width_, height_);
    HexMap<unsigned> distanceFrom(width_, height_);
    std::fill(visited.begin(), visited.end(), false);

    previous.at(start) = start;
    distanceFrom.at(start) = 0;

    std::queue<Hex> queue;
    queue.push(start);
    while (!queue.empty())
    {
        Hex current = queue.front();
        queue.pop();
        visited.at(current) = true;

        if (current == end) {
            std::vector<Hex> path;
            for (Hex step = end; step != start; step = previous.at(step)) path.push_back(step);
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (distance.at(current) == distance) continue;

        unsigned neighboringDistance = distance.at(current) + 1;

        for (Hex neighbour : getNeighbors(current)) {
            if (visited.at(neighbour) || !reachable(neighbour)) continue;
            queue.push(neighbour);
            previous.at(neighbour) = current;
            distanceFrom.at(neighbour) = neighboringDistance;
        }
    }
    return {};
}

template <typename T>
inline HexMap<bool> HexMap<T>::getReachableTiles(Hex start, std::function<bool(Hex)> &reachable, unsigned distance)
{
    return HexMap<bool>();
}

template <typename T>
inline std::size_t HexMap<T>::hexToIndex(Hex hex) const noexcept
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
