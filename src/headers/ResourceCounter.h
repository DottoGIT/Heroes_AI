/*
 * File:        ResourceCounter.h
 * Description: Keeps track of current resources player has
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2024
 */

#pragma once

#include "ResourceType.h"
#include <map>

class ResourceCounter 
{
public:
    ResourceCounter();
    int getResourceAmount(ResourceType resource) const;
    void setResourceAmount(ResourceType resource, int amount);
    void modifyResourceAmount(ResourceType resource, int delta);
    const std::map<ResourceType, int>& getAllResources() const;
private:
    std::map<ResourceType, int> resources_;
};
