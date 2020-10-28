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

    a = archive_write_new();

    archive_write_set_format_pax_restricted(a);
    archive_write_add_filter_bzip2(a);
    archive_write_open_filename(a, name.c_str());

    for(int i = 0; i < files.size(); i++)
        packageutil_write_entry(a, files.at(i));

    archive_write_close(a);
    archive_write_free(a);
}
