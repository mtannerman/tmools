#define _CRT_SECURE_NO_WARNINGS   // mvsc is whining about std::localtime security
#include <ctime>
#include <iomanip>
#include "logging.h"
#include "exceptions.h"

namespace tmools
{

inline std::string GetDateTimeStr()
{
    auto t = std::time(nullptr);
    auto* tm_ = std::localtime(&t);
    return STR(std::put_time(tm_, "%Y-%m-%d-%H-%M-%S"));
}

// possible replacement of GetDateTimeStr with chrono:
/*
#include <chrono>

string NowToString()
{
chrono::system_clock::time_point p = chrono::system_clock::now();
time_t t = chrono::system_clock::to_time_t(p);
char str[26];
ctime_s(str, sizeof str, &t);
return str;
}
*/    

inline int64_t Time::ToSeconds() const
{
	return 3600LL * hour + 60LL * min + sec;
}

inline Time Time::FromSeconds(int64_t seconds)
{
	int64_t h, m, s;
	h = seconds / 3600LL;
	seconds -= h * 3600LL;
	m = seconds / 60LL;
	seconds -= m * 60LL;
	s = seconds;
	return Time(h, m, s, 0LL);
}

inline Time Time::FromMilliSeconds(int64_t seconds)
{
	const auto millisecs = seconds % 1000LL;
	auto t = FromSeconds(seconds / 1000LL);
	t.millisec = millisecs;
	return t;
}

inline void StopWatch::Restart()
{
    start = std::chrono::system_clock::now();
}

inline double StopWatch::ElapsedTime(const Unit unit)
{
	const auto timeDiff = std::chrono::system_clock::now() - start;
    switch (unit) {
        case Unit::MILLISEC:
            return double(std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count());
        case Unit::NANOSEC:
            return double(std::chrono::duration_cast<std::chrono::nanoseconds>(timeDiff).count());
        default:
            return double(std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count()) / 1000.;
    }

    THROW(UnreachableCode, "");

    return 0.;
}

inline std::string ZeroExtendedString(const int64_t val, const int nDigits = 2)
{
    const std::string str = std::to_string(val);
    const int missing = nDigits - int(str.size());
    if (missing > 0) {
        const std::string prefix(missing, '0');
        return prefix + str;
    }

    return str;
}

}   // namespace tmools

std::ostream& operator<<(std::ostream& os, const tmools::Time& t)
{
    return os << t.hour << "::" << 
    tmools::ZeroExtendedString(t.min) << "::" << 
    tmools::ZeroExtendedString(t.sec) << "::" << 
    tmools::ZeroExtendedString(t.millisec, 3);
}