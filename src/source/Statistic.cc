/*
 * File:        Statistic.cc
 * Description: Class representing a Unit or FieldUnit statistic like Strength or Initiative
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        27.11.2024
 */

#include "Statistic.h"

Statistic::Statistic(int value)
    : value_(value)
{}

unsigned int Statistic::get() const
{
    return value_;
}

void Statistic::increase(unsigned int value)
{
    value_ += value;
}

bool Statistic::operator>(const Statistic &other) const
{
    return value_ > other.value_;
}
