#ifndef directory_h
#define directory_h

#if defined(__APPLE__)
#define DIRECTORY_SEPERATOR "/"
#endif

/**
 * @brief Scan the specified directory
 * 
 * @param path Path to the directory to be scanned
 * @return std::vector<std::string> Vector of directory contents
 */
std::vector<std::string> scan_directory(const std::string path);

/**
 * @brief Scan the specified directory
 * 
 * @param path Path to the directory to be scanned
 * @return std::vector<std::string> Vector of directory contents
 */
std::vector<std::string> scan_directory(const char *path);

/**
 * @brief Scan the specified directory
 * 
 * @param path Path to the directory to be scanned
 * @param recursive Recursive mode flag
 * @return std::vector<std::string> 
 */
std::vector<std::string> scan_directory(const std::string path, bool recursive);

/**
 * @brief Scan the specified directory
 * 
 * @param path Path to the directory to be scanned
 * @param recursive Recursive mode flag
 * @return std::vector<std::string> 
 */
std::vector<std::string> scan_directory(const char *path, bool recursive);

/**
 * @brief Scan the specified directory
 * 
 * @param items Reference to vector of directory contents
 * @param path Path to the directory to be scanned
 */
void scan_directory(std::vector<std::string> &items, const std::string path);

/**
 * @brief Scan the specified directory
 * 
 * @param items Reference to vector of directory contents
 * @param path Path to the directory to be scanned
 */
void scan_directory(std::vector<std::string> &items, const char *path);

/**
 * @brief Scan the specified directory
 * 
 * @param items Reference to vector of directory contents
 * @param path Path to the directory to be scanned
 * @param recursive Recursive mode flag
 */
void scan_directory(std::vector<std::string> &items, const std::string path, bool recursive);

/**
 * @brief Scan the specified directory
 * 
 * @param items Reference to vector of directory contents
 * @param path Path to the directory to be scanned
 * @param recursive Recursive mode flag
 */
void scan_directory(std::vector<std::string> &items, const char *path, bool recursive);

#endif /* directory_h */
