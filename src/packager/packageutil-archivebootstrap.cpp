#include <vector>
#include <string>

#include "thirdparty/libarchive/include/libarchive/archive.h"

#include "packageutil.h"

void packageutil_archiveBootstrap_create(struct archive *archive)
{
    archive = archive_write_new();
}

void packageutil_archiveBootstrap_createTar(struct archive *archive)
{
    packageutil_archiveBootstrap_create(archive);
    archive_write_set_format_pax_restricted(archive);
}

void packageutil_archiveBootstrap_close(struct archive *archive)
{
    archive_write_close(archive);
    archive_write_free(archive);
}
