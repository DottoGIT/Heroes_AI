/*
 * File:        HeroesAIExcept.h
 * Description: Defines custom exceptions
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */
#pragma once

#include <stdexcept>

class SdlException : public std::runtime_error {
public:
    explicit SdlException(const std::string& message)
        : std::runtime_error(message) {}
};