#include "Health.h"

Health::Health(unsigned int value)
    : value_(value)
{}

unsigned int Health::get() const
{
    return value_;
}

void Health::damage(unsigned int damage_value)
{
    value_ = (damage_value >= value_) ? 0 : value_ - damage_value;
}

bool Health::isAlive() const
{
    return value_ > 0;
}
