/*
 * File:        RenderObject.h
 * Description: Data containder for rendering object in Display 
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
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

struct RenderObject
{
    std::string path;
    int priority;
    int width;
    int height;
};

