/*
 * File:        MapDecoration.h
 * Description: Represents map obstacles and non-interractive elements.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        04.01.2025
 */

#pragma once
#include <string>
#include "IRenderable.h"
#include "Hex.h"

class MapDecoration : public IRenderable{
public:
    MapDecoration() = default;
    ~MapDecoration() = default;
    void setSymbol(char symbol);
    void setPosition(const Hex& position);
    char getSymbol() const;
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    char symbol_;
    Hex position_;
    Hex size_;
};