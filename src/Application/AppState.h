#ifndef APPSTATE_H
#define APPSTATE_H

#include <string>

namespace AppState {
    enum AppState {RUNNING, HALTED, FAILED};
    inline std::string toString(const AppState state) {
        switch(state) {
            case RUNNING:
                return "RUNNING";
            case HALTED:
                return "HALTED";
            case FAILED:
                return "FAILED";
            default:
                return "Literally impossible";
        }
    }
}

#endif //APPSTATE_H
