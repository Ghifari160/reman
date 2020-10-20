#include <vector>
#include <fstream>
#include <string>

#include "remanignore.h"

template<class T>
int searchInVector(const std::vector<T> &haystack, const T needle);
template<class T>
void removeFromVector(std::vector<T> &haystack, const T needle);

std::vector<std::string> read_remandignore()
{
    std::vector<std::string> ignored;

    read_remandignore(ignored);

    return ignored;
}

void read_remandignore(std::vector<std::string> &ignored)
{
    ignored.push_back(".remanignore");

    std::string line;
    std::ifstream remanignore;

    remanignore.open(".remanignore");

    if(!remanignore.is_open())
        perror("Read error .remanignore");
    else
    {
        while(getline(remanignore, line))
        {
            // TODO: Remove beginning space
            
            if(line.substr(0, 1) != "#")
            {
                if(line.substr(0, 1) == "!")
                    removeFromVector(ignored, line.substr(1));
                else
                    ignored.push_back(line);
            }
        }
    }
}

/**
 * @brief Search for an item in a vector
 * 
 * @param haystack Vector to search in
 * @param needle Item to search for
 * @return int Position of the first match as an offset from the vector's beginning iterator. If no match is found, `0` is returned.
 */
template<class T>
int searchInVector(const std::vector<T> &haystack, const T needle)
{
    int i = 0;

    for(auto it = haystack.begin(); it != haystack.end(); it++)
    {
        if(*it == needle)
            return i;
        
        i++;
    }

    return -1;
}

/**
 * @brief Remove an item from a vector
 * 
 * @param haystack Vector containing the item
 * @param needle Item to be removed
 */
template<class T>
void removeFromVector(std::vector<T> &haystack, const T needle)
{
    int pos;
    if((pos = searchInVector(haystack, needle)) > -1)
        haystack.erase(haystack.begin() + pos);
}
