#ifndef APPSTATE_H
#define APPSTATE_H

#include <string>

namespace AppState {
    enum AppState {RUNNING, HALTED, FAILED};
    inline std::string toString(const AppState state) {
        switch(state) {
            case RUNNING:
                return "RUNNING";
                break;
            case HALTED:
                return "HALTED";
                break;
            case FAILED:
                return "FAILED";
                break;
            default:
                return "Literally impossible";
        }
    }
}

#endif //APPSTATE_H
