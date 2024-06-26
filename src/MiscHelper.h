#ifndef MISCHELPER_H
#define MISCHELPER_H

#include <vector>
#include <string>

namespace helper {
    template<typename... Args>
    std::string format_g(std::string s, Args... params);

    template <typename Out>
    void split(const std::string &s, char delim, Out result);

    std::vector<std::string> split(const std::string &s, char delim);
}

#endif //MISCHELPER_H
