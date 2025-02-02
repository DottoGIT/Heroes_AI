/*
 * File:        Logger.cc
 * Description: Manages logging into log files.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

#include <iomanip>
#include "Logger.h"

std::mutex Logger::mtx_;

void Logger::log(const LogLevel& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx_);
    std::string levelString = getLogLevelString(level);
    std::string logMessage = getCurrentTime() + " [" + levelString + "] " + message;
    std::cout << logMessage << std::endl;
}

void Logger::info(const std::string& message) {
    log(LogLevel::INFO, message);
}

void Logger::warning(const std::string& message) {
    log(LogLevel::WARNING, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::ERROR, message);
}

void Logger::debug(const std::string& message) {
    log(LogLevel::DEBUG, message);
}

std::string Logger::getLogLevelString(const LogLevel& level) {
    switch (level) {
    case LogLevel::INFO:
        return "INFO";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::DEBUG:
        return "DEBUG";
    default:
        return "UNKNOWN";
    }
}

std::string Logger::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm tmNow;

#ifdef _WIN32
    localtime_s(&tmNow, &now);
#else
    localtime_r(&now, &tmNow);
#endif

    std::stringstream ss;
    ss << std::put_time(&tmNow, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
