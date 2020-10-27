#include <vector>
#include <string>
#include <iostream>
#include <dirent.h>

#include <sys/stat.h>

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
                std::string cpath, lpath;

                cpath.append(path);
                cpath.append(DIRECTORY_SEPERATOR);
                cpath.append(entry->d_name);

                if(entry->d_type == DT_DIR)
                    lpath.append("D");
                else
                    lpath.append("F");
                
                lpath.append(cpath);

                items.push_back(lpath);

                if(entry->d_type == DT_DIR && recursive)
                    scan_directory(items, cpath, recursive);
                // else
                //     items.push_back(lpath);
            }
        }
    }
}

void clean_directoryList(std::vector<std::string> &items, std::vector<std::string> &all)
{
    std::vector<std::string> dummyVector;

    clean_directoryList(items, dummyVector, dummyVector, all);
}

void clean_directoryList(std::vector<std::string> &items, std::vector<std::string> &directory, std::vector<std::string> &files, std::vector<std::string> &all)
{
    for(int i = 0; i < items.size(); i++)
    {
        if(items.at(i).substr(0, 1) == "D")
            directory.push_back(items.at(i).substr(1));
        else if(items.at(i).substr(0, 1) == "F")
            files.push_back(items.at(i).substr(1));

        all.push_back(items.at(i).substr(1));
    }
}

void get_perms(mode_t &perms, mode_t &mode)
{
    perms = (mode & DIRECTORY_MASK_PERMS);
}

void get_directory_mode(mode_t &mode, const std::string path)
{
    struct stat st;
    stat(path.c_str(), &st);
    mode = st.st_mode;
}


void get_directory_type(mode_t &type, const std::string path)
{
    mode_t mode;
    get_directory_mode(mode, path);
    get_directory_type(type, mode);
}

void get_directory_type(mode_t &type, const mode_t &mode)
{
    type = (mode & DIRECTORY_MASK_TYPE);
}

void get_directory_perms(mode_t &perms, const std::string path)
{
    mode_t mode;
    get_directory_mode(mode, path);
    get_directory_perms(perms, mode);
}

void get_directory_perms(mode_t &perms, const mode_t &mode)
{
    perms = (mode & DIRECTORY_MASK_PERMS);
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
