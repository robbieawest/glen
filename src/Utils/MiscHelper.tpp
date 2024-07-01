#ifndef MISCHELPER_TPP
#define MISCHELPER_TPP

#include <sstream>
#include <string>
#include <type_traits>


namespace helper {


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
