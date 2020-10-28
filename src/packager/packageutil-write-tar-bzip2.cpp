#include <vector>
#include <string>

#include "thirdparty/libarchive/include/libarchive/archive.h"

#include "packageutil.h"

void packageutil_write_tar_bzip2(const std::vector<std::string> &files, const std::string name)
{
    packageutil_write_tar_bzip2(files, name, false);
}

void packageutil_write_tar_bzip2(const std::vector<std::string> &files, const std::string name, bool arg_debug)
{
    struct archive *a;

    packageutil_archiveBootstrap_createTar(a);
    archive_write_add_filter_bzip2(a);
    archive_write_open_filename(a, name.c_str());

    for(int i = 0; i < files.size(); i++)
        packageutil_write_entry(a, files.at(i));

    packageutil_archiveBootstrap_close(a);
}
