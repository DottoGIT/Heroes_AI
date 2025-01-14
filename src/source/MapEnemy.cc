#include "MapEnemy.h"
#include <string>
#include "Logger.h"

MapEnemy::MapEnemy(std::shared_ptr<FieldArmy> army)
    : army_(army)
{
}

void MapEnemy::interact(MapTile& myTile)
{
    std::stringstream ss;
    ss << "Enemy encoutered, army size: " << army_->getUnits().size();
    Logger::info(ss.str());
}

void MapEnemy::setPosition(const Hex& position)
{
    position_ = position;
}

std::shared_ptr<IInteractable> MapEnemy::clone() const
{
    return std::make_unique<MapEnemy>(*this);
}

void MapEnemy::setSpritePath(const std::string& path)
{
    path_to_sprite_ = path;
};

const std::string& MapEnemy::getSpritePath() const
{
    return path_to_sprite_;
}

Hex MapEnemy::getSpriteDimensions() const
{
    return Hex(ENEMY_WIDTH, ENEMY_HEIGHT);
}

int MapEnemy::getSpritePriority() const
{
    return OBJECT_PRIORTITY_3;
}

Hex MapEnemy::getPosition() const
{
    return position_;
}

bool MapEnemy::isFlipped() const
{
    return false;
}
