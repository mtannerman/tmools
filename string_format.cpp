#include "string_format.h"




namespace tmools
{
namespace detail
{
unsigned int count_number_of_curly_bracket_pairs(const std::string& s)
{
    if (s.size() < 2) {
        return (unsigned int)0;
    }

    unsigned int counter = (unsigned int)0;
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

}
}