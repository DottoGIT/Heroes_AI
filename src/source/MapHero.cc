#include "MapHero.h"

void MapHero::setPosition(Hex position)
{
    position_ = position;
}

Hex MapHero::getPosition() const
{
    return position_;
}

const std::string& MapHero::getSpritePath() const
{
    return path_to_sprite_;
}

Hex MapHero::getSpriteDimensions() const
{
    return Hex(HERO_SPRITE_WIDTH, HERO_SPRITE_HEIGHT);
}

int MapHero::getSpritePriority() const
{
    return OBJECT_PRIORTITY_3;
}

bool MapHero::isFlipped() const
{
    return false;
}
