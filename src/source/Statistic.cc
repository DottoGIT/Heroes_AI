#include "Statistic.h"

Statistic::Statistic(int value)
{
}

unsigned int Statistic::get() const
{
    return value_;
}

void Statistic::increase(unsigned int value)
{
    value_ += value;
}
