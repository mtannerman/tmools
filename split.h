#include <string>
#include <vector>


namespace tmools
{

std::string spaces(const int len);

std::string& strip_left(std::string& str);
std::string& strip_right(std::string& str);
std::string& strip(std::string& str);

std::vector<std::string> split(const std::string& str, char delimiter = '\n');
std::vector<std::string> split(const std::string& str, const std::string& delimiter);

}