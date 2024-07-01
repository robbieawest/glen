#ifndef LOGTYPE_H
#define LOGTYPE_H

#include <string>

namespace LogType {
    enum LogType {INFO, WARNING, ERROR};
    inline std::string toString(const LogType state) {
        switch(state) {
            case INFO:
                return "INFO";
            case WARNING:
                return "WARNING";
            case ERROR:
                return "ERROR";
            default:
                return "Literally impossible";
        }
    }
}

#endif //LOGTYPE_H
