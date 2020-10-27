#ifndef packageutil_h
#define packageutil_h

/**
 * @brief Write archive entry
 * 
 * @param archive libarchive archive struct
 * @param filename Path to archive entry
 */
void packageutil_write_entry(struct archive *archive, const std::string filename);

/**
 * @brief Write archive entry
 * 
 * @param archive libarchive archive struct
 * @param filename Path to archive entry
 * @param arg_debug Debug flag. If `true`, the data buffer breakpoints for I/O will be logged in stdout
 */
void packageutil_write_entry(struct archive *archive, const std::string filename, bool arg_debug);

/**
 * @brief Write archive tarball (gzip)
 * 
 * @param files Indicator prefixless directory scan list
 * @param name Path to archive
 */
void packageutil_write_tar_gzip(const std::vector<std::string> &files, const std::string name);

/**
 * @brief Write archive tarball (gzip)
 * 
 * @param files Indicator prefixless directory scan list
 * @param name Path to archive
 * @param arg_debug Debug flag. If `true`, the data buffer breakpoints for I/O will be logged in stdout
 */
void packageutil_write_tar_gzip(const std::vector<std::string> &files, const std::string name, bool arg_debug);

#endif /* packageutil_h */
