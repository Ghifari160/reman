#ifndef remanignore_h
#define remanignore_h

/**
 * @brief Read .remanignore file
 * 
 * @return std::vector<std::string> Vector of ignored paths as configured in .remanignore
 */
std::vector<std::string> read_remandignore();

/**
 * @brief Read .remanignore file
 * 
 * @param ignored Reference to vector to be populated with ignored paths as configured in .remanignore
 */
void read_remandignore(std::vector<std::string> &ignored);

#endif /* remanignore_h */
