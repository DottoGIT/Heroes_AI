/*
 * File:        Health.h
 * Description: Class representing a FieldUnit health
 *
 * Author:      Wojciech Sarwiński
 * 
 * Date:        27.11.2024
 */

class Health
{
private:
    unsigned int value_;
public:
    Health(unsigned int value);
    unsigned int get() const;
    void damage(unsigned int damage_value);
    bool isAlive() const;

    //bool operator==(const Health& other) const;
    //bool operator!=(const Health& other) const;
    //bool operator<(const Health& other) const;
    //bool operator>(const Health& other) const;
    //bool operator<=(const Health& other) const;
    //bool operator>=(const Health& other) const;
};