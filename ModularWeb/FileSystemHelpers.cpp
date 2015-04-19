#include <dirent.h>//posix, but not standard c++
#include "FileSystemHelpers.h"

bool ListDirectory(const std::string& DirectoryPath, std::vector<std::string>& Files)
{
    DIR* dir = opendir(DirectoryPath.c_str());

    while(dirent* entry = readdir(dir))
    {
        Files.push_back(entry->d_name);//zero terminated char[]
    }
    //delete entry?
    closedir(dir);
    return true;//???
}
