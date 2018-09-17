#ifndef TMOOLS_TIME_INCLUDED
#define TMOOLS_TIME_INCLUDED

#include <cstdint>
#include <string>
#include <chrono>

namespace tmools
{

std::string GetDateTimeStr();

struct Time
{
	int64_t ToSeconds() const;

	Time() = default;
	Time(const int64_t hour, 
		const int64_t min, 
		const int64_t sec, 
		const int64_t millisec) 
		: hour(hour)
		, min(min), sec(sec)
		, millisec(millisec) 
	{}

	static Time FromSeconds(int64_t seconds);

	static Time FromMilliSeconds(int64_t seconds);

	int64_t hour;
	int64_t min;
	int64_t sec;
	int64_t millisec;
};

struct StopWatch
{
	StopWatch() { Restart(); }
	enum class Unit { MILLISEC, NANOSEC, SEC };
	void Restart();
	double ElapsedTime(const Unit unit = Unit::MILLISEC);
	std::chrono::system_clock::time_point start;
};

}   //tmools



std::ostream& operator<<(std::ostream& os, const tmools::Time& t);

#include "time.inl"

#endif   // TMOOLS_TIME_INCLUDED
