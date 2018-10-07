#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "file_operation.h"
#include "exceptions.h"
#include "string_format.h"

#ifdef TMOOLS_COUNT_CALLS_OF_LOG
#include <map>
#endif

namespace tmools
{

class LogArchiver
{
public:
	inline static std::string LogArchivePath()
	{
		// TODO
		return "";
	}

	inline static LogArchiver& GetInstance()
	{
		static LogArchiver instance;
		return instance;
	}

	inline void Add(const std::string& logString)
	{
		ofs << logString;
	}
private:
	LogArchiver() 
	{
		const auto path = LogArchivePath();
		// std::cout << "Creating LogArchiver" << std::endl;
		if (!path.empty()) {
			THROW_IF(!CreateDirectory(path), FileOperationFailure, STR("Couldn't create directory: " << path));
		}
		ofs.open(STR(path << "log.txt"));
		THROW_IF(!ofs.is_open(), FileOperationFailure, "Couldn't open log stream");
	}
	std::ofstream ofs;
};


std::string StripPrettyFunction(std::string prettyFunction)
{
	const size_t spaceAfterTypeNamePosition = prettyFunction.find(' ');
	prettyFunction = prettyFunction.substr(spaceAfterTypeNamePosition + 1);
	std::stringstream ss;
	bool inBracketRegion = false;
	char prevChar = ' ';
	for (char c : prettyFunction) {
		if (c == '(') {
			inBracketRegion = true;
		}
		else if (prevChar == ')') {
			inBracketRegion = false;
		}

		if (!inBracketRegion) {
			ss << c;
		}

		prevChar = c;
	}
	
	return ss.str();
}

namespace common_detail
{
bool count_calls()
{
#ifdef TMOOLS_COUNT_CALLS_OF_LOG
    return true;
#else
    return false;
#endif
}

#ifdef TMOOLS_COUNT_CALLS_OF_LOG
class CallCounter
{
public:
    static std::map<std::string, int>& GetInstance()
    {
        static std::map<std::string, int> instance;
        return instance;
    }
private:
    CallCounter() = default;
    CallCounter(const CallCounter&) = default;
    CallCounter& operator=(const CallCounter&) = default;
};
#endif

inline void Log(const std::string& function, const std::string& message, const int lineIndex)
{
#ifdef TMOOLS_COUNT_CALLS_OF_LOG
    const int newCount = ++CallCounter::GetInstance()[function];
	const std::string full = ::tmools::format("[{}][{}/{}] {}\n", newCount, function, lineIndex, message);
#else
	const std::string full = ::tmools::format("[{}/{}] {}\n", function, lineIndex, message);
#endif
	std::cout << full;
	LogArchiver::GetInstance().Add(full);
}


}   // common_detail
}   // tmools
