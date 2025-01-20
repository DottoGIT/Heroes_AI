/*
 * File:        ResourceCounter.h
 * Description: Keeps track of current resources player has
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        14.01.2024
 */

#pragma once
#include <map>
#include <memory>
#include <mutex>
#include "ResourceType.h"

class ResourceCounter 
{
public:
    ResourceCounter(const ResourceCounter&) = delete;
    ResourceCounter& operator=(const ResourceCounter&) = delete;
    static ResourceCounter& getInstance()
    {
        static ResourceCounter instance;
        return instance;
    }
    void setResourceAmount(const ResourceType& resource, int amount);
    void modifyResourceAmount(const ResourceType& resource, int delta);
    int getResourceAmount(const ResourceType& resource) const;
    bool allResourcesCollected() const;
    const std::map<ResourceType, int>& getAllResources() const;
private:
    ResourceCounter();
    std::map<ResourceType, int> resources_;
};