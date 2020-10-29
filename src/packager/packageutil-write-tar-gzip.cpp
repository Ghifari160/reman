#include <vector>
#include <string>

#include "libarchive/archive.h"

#include "packageutil.h"

void packageutil_write_tar_gzip(const std::vector<std::string> &files, const std::string name)
{
    packageutil_write_tar_gzip(files, name, false);
}

void packageutil_write_tar_gzip(const std::vector<std::string> &files, const std::string name, bool arg_debug)
{
    struct archive *a = archive_write_new();

    packageutil_archiveBootstrap_createTar(a);
    archive_write_add_filter_gzip(a);
    archive_write_open_filename(a, name.c_str());

    for(int i = 0; i < files.size(); i++)
        packageutil_write_entry(a, files.at(i), arg_debug);

    packageutil_archiveBootstrap_close(a);
}
