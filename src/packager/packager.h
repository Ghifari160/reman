#ifndef packager_h
#define packager_h

#pragma region print

/**
 * @brief Print the tool's version page
 * 
 */
void print_version();

/**
 * @brief Print the tool's invalid usage message
 * 
 * @param argv Starting arguments
 */
void print_invalid_usage(char** argv);

/**
 * @brief Print the tool's help page
 * 
 */
void print_help();

#pragma endregion

/**
 * @brief Wildcard string matching
 * 
 * @param str String to match
 * @param pattern Pattern to match
 * @param n Length of string
 * @param m Length of pattern
 * @return true String matches the pattern
 * @return false String does not match the pattern
 */
bool strmatch(char *str, const char *pattern, int n, int m);

#endif /* packager_h */
