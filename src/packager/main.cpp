#include <iomanip>
#include <string>
#include <vector>

#include <sys/stat.h>

#include "thirdparty/zipper/include/zipper/zipper.h"

#include "../package.h"
#include "packager.h"
#include "remanignore.h"
#include "directory.h"
#include "packageutil.h"

void processRemanIgnore(const std::vector<std::string> &ignored, std::vector<std::string> &dirs, bool debug_mode);

void packageArchive_zip(const std::vector<std::string> &dirs, const std::string &package_archiveName);
void packageArchive_zip(const std::vector<std::string> &dirs, const std::string &package_archiveName, bool verbose);

int main(int argc, char** argv)
{
    bool arg_debug = false,
         arg_help = false,
         arg_verbose = false,
         arg_version = false;

    std::string packager_target,
                project_name,
                project_version,
                package_basename;

    // Scan for arguments
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "--debug") == 0 || strcasecmp(argv[i], "-d") == 0)
        {
            arg_debug = true;
            arg_verbose = true;
        }
        else if(strcmp(argv[i], "--help") == 0)
            arg_help = true;
        else if((strcmp(argv[i], "--project-name") == 0 || strcmp(argv[i], "-p") == 0) && i + 1 < argc)
            project_name = argv[i + 1];
        else if((strcmp(argv[i], "--project-version") == 0 || strcmp(argv[i], "-v") == 0) && i + 1 < argc)
            project_version = argv[i + 1];
        else if((strcmp(argv[i], "--target") == 0 || strcmp(argv[i], "-t") == 0) && i + 1 < argc)
            packager_target = argv[i + 1];
        else if(strcmp(argv[i], "--verbose") == 0)
            arg_verbose = true;
        else if(strcmp(argv[i], "--version") == 0)
            arg_version = true;
    }

    // If information is requested, print it then exit
    if(arg_help)
    {
        print_help();

        return 0;
    }
    else if(arg_verbose)
        print_version();
    else if(arg_version)
    {
        print_version();
        
        return 0;
    }

    // Set the parameters in order if all are unset
    if(packager_target.empty() && project_name.empty() && project_version.empty())
    {
        for(int i = 0; i < argc; i++)
        {
            switch(i)
            {
                case 1:
                    packager_target = argv[i];
                    break;

                case 2:
                    project_name = argv[i];
                    break;

                case 3:
                    project_version = argv[i];
            }
        }
    }

    if(packager_target.empty() || project_name.empty() || project_version.empty())
    {
        print_invalid_usage(argv);
        return 1;
    }

    if(arg_debug || arg_verbose)
        std::cout << "Running in " << ((arg_debug) ? "DEBUG" : "VERBOSE") << " mode." << std::endl << std::endl;

    package_basename = project_name + "-v" + project_version;

    if(packager_target.substr(packager_target.size() - 1, 1) != DIRECTORY_SEPERATOR)
        packager_target.append(DIRECTORY_SEPERATOR);

    std::string package_archiveName_zip(packager_target + package_basename + ".zip"),
                package_archiveName_tgz(packager_target + package_basename + ".tar.gz"),
                package_archiveName_tbz(packager_target + package_basename + ".tar.bz2");
    
    if(arg_verbose)
    {
        std::cout << "Project Name:        " << project_name << std::endl;
        std::cout << "Project Version:     " << project_version << std::endl << std::endl;

        std::cout << "Packager Target:     " << packager_target << std::endl;
        std::cout << "Package Basename:    " << package_basename << std::endl << std::endl;

        std::cout << "Package Path (Zip):  " << package_archiveName_zip << std::endl;
        std::cout << "Package Path (TGZ):  " << package_archiveName_tgz << std::endl;
        std::cout << "Package Path (TBZ2): " << package_archiveName_tbz << std::endl << std::endl;
    }

    // TODO: actual packaging
    //
    // - [x] Read .remanignore
    // - [x] Skip .remanignore by default
    // - [x] Include .remanignore if listed as !.remanignore
    // - [x] Skip all listed in .remanignore
    // - [x] Scan all dirs
    // - [x] Zip remaining items
    // 
    // Then either:
    // 
    // - [ ] Tar remaining items
    // - [ ] GZip tarball
    // - [ ] BZ2 tarball
    // 
    // Or:
    // 
    // - [x] TGZ remaining items
    // - [ ] TBZ remaining items
    // 

    if(arg_verbose)
        std::cout << "Scanning directory contents" << std::endl;
    std::vector<std::string> items = scan_directory(".", true);

    if(arg_verbose)
        std::cout << "Reading .remanignore" << std::endl;
    std::vector<std::string> ignored = read_remandignore();

    if(arg_verbose)
        std::cout << "Processing .remanignore" << std::endl;
    processRemanIgnore(ignored, items, arg_debug);

    if(arg_verbose)
        std::cout << "Cleaning up directory scan list" << std::endl;
    std::vector<std::string> dirs, files, all;
    clean_directoryList(items, dirs, files, all);

    packageArchive_zip(files, package_archiveName_zip, arg_verbose);
    packageutil_write_tar_gzip(files, package_archiveName_tgz, arg_debug);
}

void processRemanIgnore(const std::vector<std::string> &ignored, std::vector<std::string> &dirs, bool debug_mode)
{
    for(int i = 0; i < ignored.size(); i++)
    {
        std::vector<char> pattern(ignored.at(i).c_str(), ignored.at(i).c_str() + ignored.at(i).size() + 1);

        for(int j = 0; j < dirs.size();)
        {
            std::string sdir(dirs.at(j).substr(1));
            std::vector<char> dir(sdir.c_str(), sdir.c_str() + sdir.size() + 1);

            if(strmatch(dir.data(), pattern.data(), dir.size(), pattern.size()))
            {
                if(debug_mode)
                    std::cout << dir.data() << " MATCHES pattern " << pattern.data() << ". Erasing from vector at " << j << "." << std::endl;

                dirs.erase(dirs.begin() + j);
            }
            else
            {
                if(debug_mode)
                    std::cout << dir.data() << " DOES NOT MATCH pattern " << pattern.data() << ". Increasing index." << std::endl;

                j++;
            }
        }
    }
}

void packageArchive_zip(const std::vector<std::string> &dirs, const std::string &package_archiveName)
{
    packageArchive_zip(dirs, package_archiveName, false);
}

void packageArchive_zip(const std::vector<std::string> &dirs, const std::string &package_archiveName, bool verbose)
{
    zipper::Zipper package_archive(package_archiveName);

    if(verbose)
        std::cout << "PACKAGING DIRECTORY LISTS:" << std::endl;

    for(int i = 0; i < dirs.size(); i++)
    {
        if(verbose)
            std::cout << "  " << dirs.at(i) << std::endl;

        package_archive.add(dirs.at(i), zipper::Zipper::SaveHierarchy);
    }

    package_archive.close();
}
