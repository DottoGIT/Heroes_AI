#include "Resource.h"
#include <string>
#include "Logger.h"

Resource::Resource(const ResourceType& type, int value)
    : type_(type), value_(value)
{
}

void Resource::interact(MapTile& myTile)
{
    std::stringstream ss;
    ss << "Resource collected. Value: " << value_ << ", Type: " << type_;
    Logger::info(ss.str());
}

void Resource::setPosition(const Hex& position)
{
    position_ = position;
}

std::shared_ptr<IInteractable> Resource::clone() const
{
    return std::make_unique<Resource>(*this);
}

void Resource::setSpritePath(const std::string& path)
{
    path_to_sprite_ = path;
};

const ResourceType& Resource::getType() const
{
    return type_;
}

const std::string& Resource::getSpritePath() const
{
    return path_to_sprite_;
}

Hex Resource::getSpriteDimensions() const
{
    return Hex(RESOURCE_SIZE, RESOURCE_SIZE);
}

int Resource::getSpritePriority() const
{
    return OBJECT_PRIORTITY_2;
}

Hex Resource::getPosition() const
{
    return position_;
}

bool Resource::isFlipped() const
{
    return false;
}
