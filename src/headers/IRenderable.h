/*
 * File:        IRenderable.h
 * Description: Interface for objects that can be rendered
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        02.12.2024
 */
#pragma once
#include <string>

class IRenderable
{
public:
    virtual ~IRenderable() = default;
    virtual const std::string& getPath() const = 0;
    virtual int getPriority() const = 0;
};