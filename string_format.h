#pragma once

#include "STR.h"
#include "exceptions.h"
#include <algorithm>
#include <string>

namespace tmools
{

namespace detail
{
unsigned int count_number_of_curly_bracket_pairs(const std::string& s)
{
    if (s.size() < 2) {
        return unsigned int(0);
    }

    unsigned int counter = unsigned int(0);
    auto prevIt = s.begin();
    auto it = std::next(prevIt);
    while (it != s.end()) {

        counter += (*prevIt == '{' && *it == '}') ? 1 : 0;

        ++it;
        ++prevIt;
    }

    return counter;
}

std::string replace_next_curly_bracket(
    const std::string& stringToFormat, const std::string& stringToPutIn)
{
    const auto curlyBracketPos = stringToFormat.find("{}");
    return STR(stringToFormat.substr(0, curlyBracketPos)
               << stringToPutIn << stringToFormat.substr(curlyBracketPos + 2));
}

template <typename T> std::string format_rollout(const std::string& stringToFormat, const T& v)
{
    return replace_next_curly_bracket(stringToFormat, STR(v));
}

template <typename T, typename... Args>
std::string format_rollout(const std::string& stringToFormat, const T& first, Args&&... args)
{
    const std::string formattedString = replace_next_curly_bracket(stringToFormat, STR(first));
    return format_rollout(formattedString, args...);
}
}   // namespace detail

template <typename... Args> std::string format(const std::string& stringToFormat, Args&&... args)
{
    const unsigned int nCurlyBracketPairs =
        detail::count_number_of_curly_bracket_pairs(stringToFormat);
    constexpr unsigned int nArgs = sizeof...(Args);
    ASSERT(nCurlyBracketPairs == nArgs,
        STR("#(curly bracket pairs) = " << nCurlyBracketPairs << " intead of " << nArgs << "."));
    return detail::format_rollout(stringToFormat, args...);
}
}   // namespace tmools
