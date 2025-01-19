#include "ResourceCounter.h"

ResourceCounter::ResourceCounter() 
{
    resources_ = {
        {ResourceType::Wood, 20},
        {ResourceType::Coal, 20},
        {ResourceType::Mercury, 5},
        {ResourceType::Sulfur, 5},
        {ResourceType::Crystals, 5},
        {ResourceType::Gems, 5},
        {ResourceType::Gold, 10000},
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
