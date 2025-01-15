/*
 * File:        Statistic.h
 * Description: Class representing a Unit or FieldUnit statistic like Strength or Initiative
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        27.11.2024
 */

#pragma once

class Statistic
{
private:
    unsigned int value_;
public:
    Statistic(int value);
    unsigned int get() const;
    void increase(unsigned int value);

    //bool operator==(const Statistic& other) const;
    //bool operator!=(const Statistic& other) const;
    //bool operator<(const Statistic& other) const;
    //bool operator>(const Statistic& other) const;
    //bool operator<=(const Statistic& other) const;
    //bool operator>=(const Statistic& other) const;
};
