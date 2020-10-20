#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>

#include "directory.h"

void scan_directory(std::vector<std::string> &items, const std::string path)
{
    scan_directory(items, path, false);
}

void scan_directory(std::vector<std::string> &items, const std::string path, bool recursive)
{
    scan_directory(items, path.c_str(), recursive);
}

void scan_directory(std::vector<std::string> &items, const char *path)
{
    scan_directory(items, path, false);
}

void scan_directory(std::vector<std::string> &items, const char *path, bool recursive)
{
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;

    dp = opendir(path);

    if(dp != nullptr)
    {
        while((entry = readdir(dp)))
        {
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                std::string lpath;

                lpath.append(path);
                lpath.append(DIRECTORY_SEPERATOR);
                lpath.append(entry->d_name);

                if(entry->d_type == DT_DIR && recursive)
                    scan_directory(items, lpath, recursive);
                else
                    items.push_back(lpath);
            }
        }
    }
} 

std::vector<std::string> scan_directory(const std::string path)
{
    return scan_directory(path, false);
}

std::vector<std::string> scan_directory(const std::string path, bool recursive)
{
    return scan_directory(path.c_str(), recursive);
}

std::vector<std::string> scan_directory(const char *path)
{
    return scan_directory(path, false);
}

std::vector<std::string> scan_directory(const char *path, bool recursive)
{
    std::vector<std::string> items;

    scan_directory(items, path, recursive);

    return items;
}
