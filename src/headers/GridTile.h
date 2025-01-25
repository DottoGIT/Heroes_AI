/*
 * File:        GridTile.h
 * Description: Used to draw interactble grids on battlefield.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#pragma once
#include <memory>
#include <string>
#include "IRenderable.h"
#include "Hex.h"

class GridTile : public IRenderable
{
private:
    Hex position_;
public:
    GridTile(const Hex& position);
    virtual ~GridTile() = default;
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
};