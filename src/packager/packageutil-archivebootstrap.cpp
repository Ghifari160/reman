#include <vector>
#include <string>

#include "libarchive/archive.h"

#include "packageutil.h"

void packageutil_archiveBootstrap_createTar(struct archive *archive)
{
    archive_write_set_format_pax_restricted(archive);
}

void packageutil_archiveBootstrap_close(struct archive *archive)
{
    archive_write_close(archive);
    archive_write_free(archive);
}
