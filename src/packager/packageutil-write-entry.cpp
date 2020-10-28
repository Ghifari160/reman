#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

#include <sys/stat.h>

#include "thirdparty/libarchive/include/libarchive/archive.h"
#include "thirdparty/libarchive/include/libarchive/archive_entry.h"

#include "packageutil.h"
#include "directory.h"

void packageutil_write_entry(struct archive *archive, const std::string filename)
{
    packageutil_write_entry(archive, filename, false);
}

void packageutil_write_entry(struct archive *archive, const std::string filename, bool arg_debug)
{
    struct archive_entry *entry;
    struct stat st;
    mode_t type, perms;

    size_t length, pos;
    char buff[8192]; // TODO macro this buffer size

    stat(filename.c_str(), &st);

    get_directory_type(type, st.st_mode);
    get_directory_perms(perms, st.st_mode);

    entry = archive_entry_new();
    archive_entry_set_pathname(entry, filename.c_str());
    archive_entry_set_size(entry, st.st_size);
    archive_entry_set_filetype(entry, type);
    archive_entry_set_perm(entry, perms);

    archive_entry_set_birthtime(entry, st.st_birthtimespec.tv_sec, 0);
    archive_entry_set_ctime(entry, st.st_ctimespec.tv_sec, 0);
    archive_entry_set_mtime(entry, st.st_mtimespec.tv_sec, 0);
    archive_entry_set_atime(entry, st.st_atimespec.tv_sec, 0);

    archive_write_header(archive, entry);

    if(arg_debug)
        std::cout << filename << ":" << std::endl;

    std::fstream file(filename.c_str(), std::ios::in | std::ios::binary);

    pos = 0;
    file.read(buff, sizeof(buff));
    length = file.gcount();

    while(length > 0)
    {
        if(arg_debug)
            std::cout << "(" << pos << "," << length << ") ";

        archive_write_data(archive, buff, length);

        pos += length;
        file.seekg(pos);
        file.read(buff, sizeof(buff));
        length = file.gcount();
    }

    if(arg_debug)
        std::cout << std::endl;

    archive_entry_free(entry);
}
