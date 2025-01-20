/*
 * File:        MapEnemy.h
 * Description: Represents enemy army on the map
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2025
 */

#pragma once
#include <string>
#include <memory>
#include "IInteractable.h"
#include "IRenderable.h"
#include "Army.h"

class MapTile;

constexpr const size_t ENEMY_WIDTH = 32;
constexpr const size_t ENEMY_HEIGHT = 64;

class MapEnemy : public IInteractable {
public:
    MapEnemy(const Army& army);
    ~MapEnemy() = default;
    bool interact() override;
    void setPosition(const Hex& position) override;
    void setSpritePath(const std::string& path) override;
    std::shared_ptr<IInteractable> clone() const override;
    const std::string& getSpritePath() const override;
    Hex getSpriteDimensions() const override;
    int getSpritePriority() const override;
    Hex getPosition() const override;
    bool isFlipped() const override;
    virtual MapObjectType myObjectType() const override;
private:
    Army army_;
    std::string path_to_sprite_;
    Hex position_;
};