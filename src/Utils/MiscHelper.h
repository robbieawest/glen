#ifndef MISCHELPER_H
#define MISCHELPER_H

#include <vector>
#include <string>
#include "MiscHelper.tpp"
#include "LogType.h"

namespace helper {
    std::vector<std::string> split(const std::string &s, char delim);
    std::string format(const std::string &s, std::initializer_list<std::string> params);

    void log(LogType::LogType type, const char* func, const std::string&s, std::initializer_list<std::string> params);
    void log(LogType::LogType type, const char* func, const std::string&s);
    void log(LogType::LogType type, const std::string&s, std::initializer_list<std::string> params);
    void log(LogType::LogType type, const std::string&s);
}

#endif //MISCHELPER_H
