/*
 * File:        IInteractable.h
 * Description: Interfaces for interactable objects on map (resources and enemies)
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2025
 */

#pragma once
#include <memory>
#include "Hex.h"
#include "IRenderable.h"
#include "MapObjectType.h"

class MapTile;

class IInteractable : public IRenderable {
public:
    IInteractable() = default;
    virtual ~IInteractable() = default;
    virtual bool interact() = 0; // Returns if it should disappear after interaction
    virtual void setPosition(const Hex& position) = 0;
    virtual void setSpritePath(const std::string& path) = 0;
    virtual std::shared_ptr<IInteractable> clone() const = 0;
    virtual MapObjectType myObjectType() const = 0;

};