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

class Logger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    static void log(LogLevel level, const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void debug(const std::string& message);

private:
    static std::mutex mtx;
    static std::string getLogLevelString(LogLevel level);
    static std::string getCurrentTime();
};
