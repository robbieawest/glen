#ifndef MISCHELPER_TPP
#define MISCHELPER_TPP

#include <sstream>
#include <iterator>
#include <string>
#include <format>

namespace helper {
    template<typename... Args>
    std::string format(std::string s, Args... params) {
        return std::vformat(s, std::make_format_args(params...));
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
