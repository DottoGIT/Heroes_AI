/*
 * File:        Logger.h
 * Description: Manages logging into log files.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <sstream>
#include <ctime>
#include "LogLevel.h"

class Logger {
public:
    static void log(const LogLevel& level, const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void debug(const std::string& message);
private:
    static std::mutex mtx_;
    static std::string getLogLevelString(const LogLevel& level);
    static std::string getCurrentTime();
};
