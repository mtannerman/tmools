#include "split.h"
#include <algorithm>
#include <sstream>

namespace tmools
{

std::string spaces(const int len)
{
    return std::string(len, ' ');
}


std::string& strip_left(std::string& str) {
	str.erase(str.begin(), std::find_if(str.begin(), str.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return str;
}

std::string& strip_right(std::string& str) {
	str.erase(std::find_if(str.rbegin(), str.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
	return str;
}

std::string& strip(std::string& str) {
	return strip_left(strip_right(str));
}

std::vector<std::string> split(const std::string& str, char delimiter /* = '\n'*/) {
	std::vector<std::string> ret;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delimiter)) {
		ret.push_back(item);
	}

	return ret;
}

std::vector<std::string> split(const std::string& str, const std::string& delimiter)
{
	if (delimiter.empty()) {
		return{ str };
	}

	std::vector<std::string> ret;
	size_t start = 0;
	size_t end = str.find(delimiter);
	while (end != std::string::npos) {
		ret.emplace_back(str.substr(start, end - start));			
		start = end + delimiter.length();
		end = str.find(delimiter, start);
	}

	ret.emplace_back(str.substr(start, end));
	return ret;
}


}