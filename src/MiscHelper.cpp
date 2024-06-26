#include "MiscHelper.h"

#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <format>

template<typename... Args>
std::string helper::format_g(std::string s, Args... params) {
	return std::vformat(s, std::make_format_args(params...));
}

template <typename Out>
void helper::split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> helper::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
