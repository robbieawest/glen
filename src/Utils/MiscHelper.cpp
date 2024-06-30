#include <vector>
#include <iterator>
#include <string>
#include "spdlog/spdlog.h"
#include "MiscHelper.h"
#include "MiscHelper.tpp"

std::vector<std::string> helper::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

