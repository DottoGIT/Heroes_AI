/*
 * File:        ResourceCounter.cc
 * Description: Keeps track of current resources player has
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2024
 */

#include "ResourceCounter.h"

ResourceCounter::ResourceCounter() 
{
    resources_ = {
        {ResourceType::WOOD, 0},
        {ResourceType::COAL, 0},
        {ResourceType::MERCURY, 0},
        {ResourceType::SULFUR, 0},
        {ResourceType::CRYSTALS, 0},
        {ResourceType::GEMS, 0},
        {ResourceType::GOLD, 0},
    };
}

int ResourceCounter::getResourceAmount(const ResourceType& resource) const 
{
    auto it = resources_.find(resource);
    if (it != resources_.end()) {
        return it->second;
    }
    return 0;
}

void ResourceCounter::setResourceAmount(const ResourceType& resource, int amount) 
{
    resources_[resource] = amount;
}

void ResourceCounter::modifyResourceAmount(const ResourceType& resource, int delta) 
{
    resources_[resource] += delta;
}

const std::map<ResourceType, int>& ResourceCounter::getAllResources() const 
{
    return resources_;
}

bool ResourceCounter::allResourcesCollected() const
{
    return 
        getResourceAmount(ResourceType::WOOD)       == 3 &&
        getResourceAmount(ResourceType::COAL)       == 3 &&
        getResourceAmount(ResourceType::MERCURY)    == 2 &&
        getResourceAmount(ResourceType::SULFUR)     == 1 &&
        getResourceAmount(ResourceType::CRYSTALS)   == 2 &&
        getResourceAmount(ResourceType::GEMS)       == 1 &&
        getResourceAmount(ResourceType::GOLD)       == 3000;
}
