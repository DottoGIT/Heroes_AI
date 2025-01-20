/*
 * File:        FieldUnitRenderable.h
 * Description: Simplifies Unit class deviding it into seperate Renderable Class.
 *
 * Author:      Wojciech Sarwinski <https://github.com/sarwoj>
 * 
 * Date:        17.01.2025
 */

#pragma once
#include "IRenderable.h"
#include "FieldUnit.h"
#include "ArmyType.h"

class FieldUnitRenderable : public IRenderable
{
public:
    FieldUnitRenderable(const FieldUnit& unit, const std::string& path_to_idle, const std::string& path_to_dead, const ArmyType& army);
    virtual ~FieldUnitRenderable() = default;
    virtual const std::string& getSpritePath() const override;
    virtual Hex getSpriteDimensions() const override;
    virtual int getSpritePriority() const override;
    virtual Hex getPosition() const override;
    virtual bool isFlipped() const override;
private:
    Hex position_;
    bool alive_;
    std::string path_to_idle_;
    std::string path_to_dead_;
    bool flipped_;
};