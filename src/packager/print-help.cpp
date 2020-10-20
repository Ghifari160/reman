#include <iostream>

#include "packager.h"

void print_help()
{
    std::cout
    << "  -d,  --debug           Debug mode. Print all argument-parameter mapping." << std::endl
    << "       --help            Print this message." << std::endl
    << "  -p,  --project-name    Project name." << std::endl
    << "  -v,  --project-version Project version without the \"v\" prefix." << std::endl
    << "  -t,  --target          Path to the packaging target directory." << std::endl
    << "       --verbose         Run in verbose mode." << std::endl
    << "       --version         Print the version of this tool." << std::endl;
}
