/*
 * File:        LogLevel.h
 * Description: Describes different logging priorities.
 *
 * Author:      Maciej Scheffer <https://github.com/DottoGIT>
 * 
 * Date:        01.12.2024
 */

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

inline std::ostream& operator<<(std::ostream& os, LogLevel type) {
    switch (type) {
        case LogLevel::INFO:
            os << "Info";
            break;
        case LogLevel::WARNING:
            os << "Warning";
            break;
        case LogLevel::ERROR:
            os << "Error";
            break;
        case LogLevel::DEBUG:
            os << "Debug";
            break;
        default:
            os << "Unknown LogLevel";
            break;
    }
    return os;
}