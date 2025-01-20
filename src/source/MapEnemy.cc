/*
 * File:        MapEnemy.cc
 * Description: Represents enemy army on the map
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2025
 */

#include <string>
#include "MapEnemy.h"
#include "Logger.h"

MapEnemy::MapEnemy(const Army& army)
    : army_(std::move(army))
{
}

bool MapEnemy::interact()
{
    std::stringstream ss;
    ss << "Enemy encoutered, army size: " << army_.getUnits().size();
    Logger::info(ss.str());
    return false;
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

MapObjectType MapEnemy::myObjectType() const
{
    return MapObjectType::ENEMY;
}