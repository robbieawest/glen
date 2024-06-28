#include "MiscHelper.h"
#include "MiscHelper.tpp"

#include <vector>
#include <iterator>
#include <string>

std::vector<std::string> helper::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
