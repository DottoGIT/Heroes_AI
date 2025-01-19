/*
 * File:        Resource.h
 * Description: Represents map resource such as gold, gems, coal etc.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2024
 */

#pragma once

#include <string>

#include "IInteractable.h"
#include "IRenderable.h"
#include "ResourceType.h"

class MapTile;

constexpr const size_t RESOURCE_SIZE = 32;

class Resource : public IInteractable {
public:
    Resource(const ResourceType& type, int value);
    ~Resource() = default;

    bool interact() override;
    void setPosition(const Hex& position) override;
    void setSpritePath(const std::string& path) override;
    std::shared_ptr<IInteractable> clone() const override;

    const ResourceType& getType() const;

    const std::string& getSpritePath() const override;
    Hex getSpriteDimensions() const override;
    int getSpritePriority() const override;
    Hex getPosition() const override;
    bool isFlipped() const override;
    
    virtual MapObjectType myObjectType() const override;

private:
    ResourceType type_;
    int value_;
    Hex position_;
    std::string path_to_sprite_;
};