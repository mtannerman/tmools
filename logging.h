#ifndef TMOOLS_LOGGING_INCLUDED
#define TMOOLS_LOGGING_INCLUDED

#include <string>
#include <sstream>

#include "STR.h"

// #define LOG(msg) ::tmools::common_detail::Log(__PRETTY_FUNCTION__, STR(msg));
#define TMOOLS_FANCY_FUNCTION ::tmools::StripPrettyFunction(__FUNCTION__)
#define LOG(msg) ::tmools::common_detail::Log(::tmools::LogData(__FILE__, TMOOLS_FANCY_FUNCTION, STR(msg), __LINE__));
#define LOG_SCOPE_ENDPOINTS(msg) ::tmools::ScopedEndpointLogger(::tmools::LogData(__FILE__, TMOOLS_FANCY_FUNCTION, STR(msg), __LINE__));

#define DESC(x) #x << ": " << x

// #define TMOOLS_COUNT_CALLS_OF_LOG


namespace tmools
{

std::string StripPrettyFunction(std::string prettyFunction);

template <typename CollectionT>
std::string CollectionToStr(const CollectionT& collection, const std::string delimiter = "")
{
    if (collection.size() == 0) {
        return "";
    }

    std::stringstream ss;
    auto lastElem = prev(end(collection));
    for (auto it = begin(collection); it != lastElem; ++it) {
        ss << *it << delimiter;
    }
    ss << *lastElem;

    return ss.str();
}

template <typename CollectionT, typename ToStringF>
std::string CollectionToStr(const CollectionT& collection, ToStringF toStringFunction, const std::string delimiter = "")
{
    if (collection.size() == 0) {
        return "";
    }

    std::stringstream ss;
    auto lastElem = prev(end(collection));
    for (auto it = begin(collection); it != lastElem; ++it) {
        ss << toStringFunction(*it) << delimiter;
    }
    ss << toStringFunction(*lastElem);

    return ss.str();
}

struct LogData
{
    LogData(const std::string& fullPath,
            const std::string& function,
            const std::string& message,
            const int lineIndex)
        : fullPath(fullPath)
        , function(function)
        , message(message)
        , lineIndex(lineIndex)
    {}

    const std::string fullPath;
    const std::string function;
    const std::string message;
    const int lineIndex;
};

class ScopedEndpointLogger
{
public:
    ScopedEndpointLogger(const LogData& l);
    ~ScopedEndpointLogger();

private:
    const LogData logData;
};


namespace common_detail
{
void Log(const LogData& l);
}
}

#include "logging.inl"

#endif   // TMOOLS_LOGGING_INCLUDED
