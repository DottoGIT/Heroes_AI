#pragma once
#include "IRenderable.h"
#include "FieldUnit.h"

enum class ArmyType;

class FieldUnitRenderable : public IRenderable
{
public:
    FieldUnitRenderable(FieldUnit unit, std::string path_to_idle, std::string path_to_dead, ArmyType army);
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