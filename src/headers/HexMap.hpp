/*
 * File:        Hex.h
 * Description: Implements hexagonal grid HexMap
 *              Based on article Hexagonal Grids from Red Blob Games
 *              link: https://www.redblobgames.com/grids/hexagons/
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        05.11.2024
 */
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
    void setData(std::vector<T>& data_);
    std::vector<T>& getDataVector();                    // Used by InputController
    const std::vector<T>& getConstDataVector() const;   // Used by Display
    T& at(Hex hex);
    const T& at(const Hex& hex) const;
    bool inBounds(const Hex& hex) const;
    std::vector<Hex> getNeighbors(const Hex& hex) const;
    std::vector<Hex> findPath(const Hex& start, const Hex& end, const std::function<bool(Hex)>& reachable) const;
    std::vector<Hex> findPath(const Hex& start, const Hex& end, const std::function<bool(Hex)>& reachable, unsigned distance) const;
    std::vector<Hex> getReachableTiles(const Hex& start, const std::function<bool(Hex)>& reachable, unsigned distance) const;
    size_t getWidth() const;
    size_t getHeight() const;
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
    std::size_t hexToIndex(const Hex& hex) const noexcept;
};

template <typename T>
HexMap<T>::HexMap(std::size_t width, std::size_t height)
    : width_(width), height_(height), data_(width * height)
{}

template <typename T>
void HexMap<T>::setData(std::vector<T>& data)
{
    if(data.size() != data_.size())
        throw std::out_of_range("Data sizes do not match!");
    data_ = data;
}

template <typename T>
std::vector<T>& HexMap<T>::getDataVector()
{
    return data_;
}

template <typename T>
const std::vector<T>& HexMap<T>::getConstDataVector() const
{
    return data_;
}

template <typename T>
T& HexMap<T>::at(Hex hex)
{
    if (!inBounds(hex))
        throw std::out_of_range("Column or row out of range!");
    std::size_t index = hexToIndex(hex);
    
    return data_[index];
}

template <typename T>
const T& HexMap<T>::at(const Hex& hex) const
{
    if (!inBounds(hex))
        throw std::out_of_range("Column or row out of range!");
    std::size_t index = hexToIndex(hex);
    
    return data_[index];
}

template <typename T>
bool HexMap<T>::inBounds(const Hex& hex) const
{
    if (hex.r < 0 || hex.r >= height_)
        return false;
    if ((hex.q + hex.r / 2) < 0 || (hex.q + hex.r / 2) >= width_)
        return false;
    return true;
}

template <typename T>
size_t HexMap<T>::getWidth() const
{
    return width_;
}

template <typename T>
size_t HexMap<T>::getHeight() const
{
    return height_;
}

template <typename T>
inline std::vector<Hex> HexMap<T>::getNeighbors(const Hex& hex) const
{
    std::vector<Hex> neighbors;

    for (Hex neighbour : hex.neighbors()) {
        if (inBounds(neighbour)) {
            neighbors.push_back(neighbour);
        }
    }
    return neighbors;
}

template <typename T>
inline std::vector<Hex> HexMap<T>::findPath(const Hex& start, const Hex& end, const std::function<bool(Hex)>& reachable) const
{
    if (!reachable(end) || !inBounds(end)) return {};

    HexMap<Hex> previous(width_, height_);
    HexMap<uint8_t> visited(width_, height_);
    std::fill(visited.begin(), visited.end(), false);

    previous.at(start) = start;
    visited.at(start) = true;

    std::queue<Hex> queue;
    queue.push(start);
    while (!queue.empty())
    {
        Hex current = queue.front();
        queue.pop();

        if (current == end) {
            std::vector<Hex> path;
            for (Hex step = end; step != start; step = previous.at(step)) path.push_back(step);
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (Hex neighbour : getNeighbors(current)) {
            if (visited.at(neighbour) || !reachable(neighbour)) continue;
            visited.at(neighbour) = true;
            queue.push(neighbour);
            previous.at(neighbour) = current;
        }
    }
    return {};
}

template <typename T>
inline std::vector<Hex> HexMap<T>::findPath(const Hex& start, const Hex& end, const std::function<bool(Hex)>& reachable, unsigned distance) const
{
    if (!reachable(end) || !inBounds(end) || distance == 0) return {};

    HexMap<Hex> previous(width_, height_);
    HexMap<uint8_t> visited(width_, height_);
    HexMap<unsigned> distanceFrom(width_, height_);
    std::fill(visited.begin(), visited.end(), false);

    previous.at(start) = start;
    visited.at(start) = true;
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

        if (distanceFrom.at(current) == distance) continue;

        unsigned neighboringDistance = distanceFrom.at(current) + 1;

        for (Hex neighbour : getNeighbors(current)) {
            if (visited.at(neighbour) || !reachable(neighbour)) continue;
            visited.at(neighbour) = true;
            queue.push(neighbour);
            previous.at(neighbour) = current;
            distanceFrom.at(neighbour) = neighboringDistance;
        }
    }
    return {};
}

template <typename T>
inline std::vector<Hex> HexMap<T>::getReachableTiles(const Hex& start, const std::function<bool(Hex)> &reachable, unsigned distance) const
{
    if (distance == 0) return {};

    HexMap<Hex> previous(width_, height_);
    HexMap<uint8_t> visited(width_, height_);
    HexMap<unsigned> distanceFrom(width_, height_);
    std::fill(visited.begin(), visited.end(), false);

    previous.at(start) = start;
    visited.at(start) = true;
    distanceFrom.at(start) = 0;

    std::queue<Hex> queue;
    queue.push(start);
    std::vector<Hex> result;
    while (!queue.empty())
    {
        Hex current = queue.front();
        queue.pop();
        visited.at(current) = true;
        result.push_back(current);
        if (distanceFrom.at(current) == distance) continue;

        unsigned neighboringDistance = distanceFrom.at(current) + 1;

        for (Hex neighbour : getNeighbors(current)) {
            if (visited.at(neighbour) || !reachable(neighbour)) continue;
            visited.at(neighbour) = true;
            queue.push(neighbour);
            previous.at(neighbour) = current;
            distanceFrom.at(neighbour) = neighboringDistance;
        }
    }
    return result;
}

template <typename T>
inline std::size_t HexMap<T>::hexToIndex(const Hex& hex) const noexcept
{
    return hex.r * width_ + (hex.q + hex.r / 2);
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
    int r = static_cast<int>(index / map->width_);
    int q = static_cast<int>(index % map->width_);
    return Hex(q - r / 2, r);
}
