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

constexpr int GIZMOS_PRIORTITY = 1;

constexpr int OBJECT_PRIORTITY_1 = 2;
constexpr int OBJECT_PRIORTITY_2 = 3;
constexpr int OBJECT_PRIORTITY_3 = 4;

constexpr int UI_PRIORTITY_1 = 5;
constexpr int UI_PRIORTITY_2 = 6;
constexpr int UI_PRIORTITY_3 = 7;

class IRenderable
{
public:
    virtual ~IRenderable() = default;
    virtual const std::string& getSpritePath() const = 0;
    virtual int getPriority() const = 0;
};