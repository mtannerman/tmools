#ifndef TMOOLS_LOGGING_INCLUDED
#define TMOOLS_LOGGING_INCLUDED

#include <string>
#include <sstream>

#define STR(expression) (((::std::ostringstream *)&(::std::ostringstream() << "" << expression))->str())
// #define LOG(msg) ::tmools::common_detail::Log(__PRETTY_FUNCTION__, STR(msg));
#define CBR_FANCY_FUNCTION ::tmools::StripPrettyFunction(__FUNCTION__)
#define LOG(msg) ::tmools::common_detail::Log(CBR_FANCY_FUNCTION, STR(msg));


#define DESC(x) #x << ": " << x

namespace tmools
{

std::string StripPrettyFunction(std::string prettyFunction);

template <typename CollectionT>
std::string CollectionToStr(const CollectionT& collection, const std::string delimiter = "")
{
    if (size(collection) == 0) {
        return "";
    }

    std::stringstream ss;
    auto lastElem = prev(end(collection));
    for (auto it = begin(collection); it != lastElem; ++it)
        ss << *it << delimiter;
    }
    ss << *lastElem;

    return ss.str();
}

template <typename CollectionT, typename ToStringF>
std::string CollectionToStr(const CollectionT& collection, ToStringF toStringFunction, const std::string delimiter = "")
{
    if (size(collection) == 0) {
        return "";
    }

    std::stringstream ss;
    auto lastElem = prev(end(collection));
    for (auto it = begin(collection); it != lastElem; ++it)
        ss << toStringFunction(*it) << delimiter;
    }
    ss << toStringFunction(*lastElem) << delimiter;

    return ss.str();
}

namespace common_detail
{
void Log(const std::string& function, const std::string& message);
}
}

#include "logging.inl"


#endif   // TMOOLS_LOGGING_INCLUDED
