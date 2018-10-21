#include "sys/types.h"
#include "sys/stat.h"
#include <cstdlib>
#include "logging.h"
#include "exceptions.h"
#include <algorithm>
#include <iostream>

// could use _MSC_VER for this
#ifdef _WIN32
#include <direct.h>
#define NOMINMAX
#include <windows.h>
#define getcwd _getcwd // MSFT "deprecation" warning
#else
#include <unistd.h>
#endif

namespace tmools {

bool IsDirectoryOrFileExist(const std::string& path)
{
    struct stat info;
    return stat(path.c_str(), &info) == 0;
}

bool IsDirectory(const std::string& path) 
{
    if (IsDirectoryOrFileExist(path)) {
        struct stat info;
        stat(path.c_str(), &info);
		auto ret = int(info.st_mode) & S_IFDIR;
        return ret != 0;
    }

    return false;
}

bool CreateDirectory(const std::string& path) 
{
#if defined(__GNUG__)
	return system(STR("mkdir -p " << path).c_str()) == 0;
#endif
#if defined(_WIN32)
	if (!IsDirectoryOrFileExist(path)) {
		std::string pathWithBackSlashes = path;
		std::replace(pathWithBackSlashes.begin(), pathWithBackSlashes.end(), '/', '\\');
		system(STR("md " << pathWithBackSlashes).c_str());
	}
	/*const auto ret = CreateDirectoryA(path.c_str(), NULL);
	std::cout << ret << std::endl;
	if (ret == EEXIST) {
		std::cout << "Directory was not created because " << path << " is the name of an existing file, directory, or device." << std::endl;
	}
	else if (ret == ENOENT) {
		std::cout << "Path was not found." << std::endl;
	}
	else if (ret == EPERM) {
		std::cout << "Permission problems during directory creation." << std::endl;
	}*/
	return IsDirectoryOrFileExist(path);
#endif
	THROW(UnImplementedFeature, "");
	return false;
}

}
