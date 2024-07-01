#include <vector>
#include <iostream>
#include <iterator>
#include <string>
#include <time.h>
#include "MiscHelper.h"
#include "LogType.h"
#include "MiscHelper.tpp"

std::vector<std::string> helper::split(const std::string &s, const char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::string helper::format(const std::string &s, const std::initializer_list<std::string> params) {
    auto params_iter = params.begin();
    std::stringstream currentPartition;
    std::stringstream res;
    bool openbrac = false;

    for(const char& currChar : s) {
        if(openbrac && currChar == '}') {
            res << currentPartition.str();
            if(params_iter != params.end())
                res << *(params_iter++);
            else
                log(LogType::ERROR, __func__, "number of bracket catchments is not equal to the number of given parameters");
            currentPartition.str(std::string());
        }
        openbrac = currChar == '{';
        if(!openbrac)
            currentPartition << currChar;
    }

    return res.str();
}

std::ostream& from_log_type(const LogType::LogType logType) {
    switch(logType) {
        case LogType::ERROR:
        case LogType::WARNING:
            return std::cerr;
        case LogType::INFO:
            return std::cout;
    }
    return std::cout;
}

std::string currentTimeAsString() {
    time_t _tm = time(nullptr);
    const tm* currTime = localtime(&_tm);
    return asctime(currTime);
}

//Maybe can use macro invocation instead of a function directly to get func, file, line input correctly

void helper::log(const LogType::LogType type, const char* func, const std::string&s, const std::initializer_list<std::string> params) {
    std::ostream& outStream = from_log_type(type);
    outStream << currentTimeAsString() << "  [" + toString(type) + ']' << "\r\n\t\t"
        <<  "[" << func << "] : " << "Line " << __LINE__ << " File " << __FILE__
        << format(s, params) << "\r\n";
}

void helper::log(const LogType::LogType type, const std::string&s, const std::initializer_list<std::string> params) {
    std::ostream& outStream = from_log_type(type);
    outStream << currentTimeAsString() << "  [" + toString(type) + ']' << "\r\n\t\t"
        << "Line " << __LINE__ << " File " << __FILE__
        << format(s, params) << "\r\n";
}

void helper::log(const LogType::LogType type, const char* func, const std::string &s) {
    log(type, func, s, {});
}

void helper::log(const LogType::LogType type, const std::string &s) {
    log(type, s, {});
}

