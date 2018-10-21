#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "file_operation.h"
#include "exceptions.h"
#include "string_format.h"
#include "logging.h"

#ifdef TMOOLS_COUNT_CALLS_OF_LOG
#include <map>
#endif

namespace tmools
{

class LogArchiver
{
public:
	static std::string LogArchivePath()
	{
		// TODO
		return "";
	}

	static LogArchiver& GetInstance()
	{
		static LogArchiver instance;
		return instance;
	}

	void Add(const std::string& logString)
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

std::string get_file_name_from_full_path(const std::string& fullPath)
{
    const size_t found = fullPath.find_last_of("/\\");
    return fullPath.substr(found + 1U);
}

std::string LogMessage(const LogData& l)
{
    const std::string& fullPath = l.fullPath;
    const std::string& function = l.function;
    const std::string& message = l.message;
    const int lineIndex = l.lineIndex;

    const std::string fileName = get_file_name_from_full_path(fullPath);
#ifdef TMOOLS_COUNT_CALLS_OF_LOG
    const int newCount = ++CallCounter::GetInstance()[function];
	return ::tmools::format("[{}][{}/{}][{}] {}\n", newCount, fileName, lineIndex, function, message);
#else
	return ::tmools::format("[{}/{}][{}] {}\n", fileName, lineIndex, function, message);
#endif
}

void Log(const LogData& l)
{
    const std::string logMessage = LogMessage(l);
	std::cout << logMessage;
	LogArchiver::GetInstance().Add(logMessage);
}


}   // common_detail

ScopedEndpointLogger::ScopedEndpointLogger(const LogData& logData) 
    : logData(logData)
{
    const auto& l = logData;
    const std::string beginMsg = "BEGIN " + l.message;
    common_detail::Log(LogData(l.fullPath, l.function, beginMsg, l.lineIndex));    
}

ScopedEndpointLogger::~ScopedEndpointLogger()
{
    const auto& l = logData;
    const std::string beginMsg = "END " + l.message;
    common_detail::Log(LogData(l.fullPath, l.function, beginMsg, l.lineIndex));    
}

}   // tmools
