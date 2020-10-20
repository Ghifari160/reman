#include <iostream>

#include "packager.h"

void print_invalid_usage(char** argv)
{
    std::cerr << "Invalid usage." << std::endl;

    std::cerr << argv[0] << " [target] [project name] [project version]" << std::endl;

    print_help();
}
