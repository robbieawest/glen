#ifndef MISCHELPER_TPP
#define MISCHELPER_TPP

#include <sstream>
#include <string>

#include "spdlog/spdlog.h"

namespace helper {

    template <typename T>
    std::string format(const std::string &s, std::initializer_list<T> params) {
        auto params_iter = params.begin();
        std::stringstream currentPartition;
        std::stringstream res;
        bool openbrac = false;

        for(const char& currChar : s) {
            if(openbrac && currChar == '}') {
                res << currentPartition.str();
                if(params_iter != params.end()) {
                    if constexpr (std::is_convertible_v<T, std::string>)
                        res << std::string(*(params_iter++));
                    else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
                        res << std::to_string(*(params_iter++));
                    else
                        spdlog::error("helper::format: input param is not convertible");
                }
                else
                    spdlog::error("helper::format: number of bracket catchments is not equal to the number of given parameters");
                currentPartition.str(std::string());
            }
            openbrac = currChar == '{';
            if(!openbrac)
                currentPartition << currChar;
        }

        return res.str();
    }

    template <typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, delim)) {
            *result++ = item;
        }
    }
}

#endif //MISCHELPER_TPP
