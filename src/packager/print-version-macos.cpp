#include <iostream>

#include "../package.h"

#if defined(__APPLE__)
void print_version()
{
    std::cout << PACKAGE_NAME << " v" << PACKAGE_VERSION << " (macOS)" << std::endl;
    std::cout << "(C) " <<  PACKAGE_AUTHOR << std::endl;
    std::cout << std::endl;
}
#endif
