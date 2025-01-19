#include "ResourceCounter.h"

ResourceCounter::ResourceCounter() 
{
    resources_ = {
        {ResourceType::Wood, 0},
        {ResourceType::Coal, 0},
        {ResourceType::Mercury, 0},
        {ResourceType::Sulfur, 0},
        {ResourceType::Crystals, 0},
        {ResourceType::Gems, 0},
        {ResourceType::Gold, 0},
    };
}

int ResourceCounter::getResourceAmount(ResourceType resource) const 
{
    auto it = resources_.find(resource);
    if (it != resources_.end()) {
        return it->second;
    }
    return 0;
}

void ResourceCounter::setResourceAmount(ResourceType resource, int amount) 
{
    resources_[resource] = amount;
}

void ResourceCounter::modifyResourceAmount(ResourceType resource, int delta) 
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
        getResourceAmount(ResourceType::Wood)       == 3 &&
        getResourceAmount(ResourceType::Coal)       == 3 &&
        getResourceAmount(ResourceType::Mercury)    == 2 &&
        getResourceAmount(ResourceType::Sulfur)     == 1 &&
        getResourceAmount(ResourceType::Crystals)   == 2 &&
        getResourceAmount(ResourceType::Gems)       == 1 &&
        getResourceAmount(ResourceType::Gold)       == 3000;
}
