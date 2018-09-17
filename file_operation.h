#ifndef TMOOLS_FILE_OPERATION_DEFINED
#define TMOOLS_FILE_OPERATION_DEFINED

#include <string>



namespace tmools {

bool IsDirectoryOrFileExist(const std::string& path);
bool IsDirectory(const std::string& path);
bool CreateDirectory(const std::string& path);

}

#include "file_operation.inl"

#endif   // TMOOLS