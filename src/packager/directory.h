#ifndef directory_h
#define directory_h

#if defined(__APPLE__)
#define DIRECTORY_SEPERATOR "/"
#endif

#if defined(S_FMT)
#define DIRECTORY_MASK_TYPE S_FMT
#else
#define DIRECTORY_MASK_TYPE 0xF000
#endif

#define DIRECTORY_MASK_EXTRA 0x7

#define DIRECTORY_MASK_PERMS 0x1FF

/**
 * @brief Get the file or directory stat mode
 * 
 * @param mode File or directory mode
 * @param path Path to file or directory
 */
void get_directory_mode(mode_t &mode, const std::string path);

/**
 * @brief Get the file or directory type
 * 
 * @param type File or directory type
 * @param path Path to file or directory
 */
void get_directory_type(mode_t &type, const std::string path);

/**
 * @brief Get the file or directory type
 * 
 * @param type File or directory type
 * @param mode File or directory mode (output of get_directory_mode())
 */
void get_directory_type(mode_t &type, const mode_t &mode);

/**
 * @brief Get the file or directory permissions
 * 
 * @param perms File or directory permissions
 * @param path Path to file or directory
 */
void get_directory_perms(mode_t &perms, const std::string path);

/**
 * @brief Get the file or directory permissions
 * 
 * @param perms File or directory permissions
 * @param mode File or directory mode (output of get_directory_mode())
 */
void get_directory_perms(mode_t &perms, const mode_t &mode);

/**
 * @brief Clean up directory scan list
 * 
 * @param items Directory scan list
 * @param all Directory scan list without indicator prefix
 */
void clean_directoryList(std::vector<std::string> &items, std::vector<std::string> &all);

/**
 * @brief Clean up directory scan list
 * 
 * @param items Directory scan list
 * @param directory Scanned subdirectories
 * @param files Scanned files
 * @param all Directory scan list without indicator prefix
 */
void clean_directoryList(std::vector<std::string> &items, std::vector<std::string> &directory, std::vector<std::string> &files, std::vector<std::string> &all);

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
