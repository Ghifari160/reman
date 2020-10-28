#include <vector>
#include <string>

#include "thirdparty/libarchive/include/libarchive/archive.h"

#include "packageutil.h"

void packageutil_write_zip(const std::vector<std::string> &files, const std::string name)
{
    packageutil_write_zip(files, name, false);
}

void packageutil_write_zip(const std::vector<std::string> &files, const std::string name, bool arg_debug)
{
    struct archive *a;

    packageutil_archiveBootstrap_create(a);
    archive_write_set_format_zip(a);
    archive_write_open_filename(a, name.c_str());

    for(int i = 0; i < files.size(); i++)
        packageutil_write_entry(a, files.at(i), arg_debug);

    packageutil_archiveBootstrap_close(a);
}
