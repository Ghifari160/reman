# Building and packaging libarchive for ReMan

Setup the directory structure

``` shell
mkdir -p out/build out/packaging/bin out/packaging/include/libarchive out/release
```

Run the following build and test

``` shell
cd out/build && \
cmake ../../ \
-DENABLE_LZMA:BOOL=OFF \
-DENABLE_LIBXML2:BOOL=OFF \
-DENABLE_ICONV:BOOL=OFF \
-DENABLE_TAR:BOOL=OFF \
-DENABLE_CPIO:BOOL=OFF \
-DENABLE_CAT:BOOL=OFF \
-DENABLE_XATTR:BOOL=OFF \
-DENABLE_ACL:BOOL=OFF \
-DENABLE_ICONV:BOOL=OFF \
-DENABLE_INSTALL:BOOL=OFF \
-DENABLE_TAR_SHARED:BOOL=OFF \
-DENABLE_CPIO_SHARED:BOOL=OFF \
-DENABLE_CAT:BOOL=OFF \
-DENABLE_CAT_SHARED:BOOL=OFF \
-DENABLE_BZip2:BOOL=OFF \
-DENABLE_ZLIB:BOOL=OFF \
&& make && make test; \
cd ../../
```

**Note:** These test failures are _acceptable_.

``` shell
99% tests passed, 4 tests failed out of 572

Total Test time (real) =  71.83 sec

The following tests FAILED:
	421 - libarchive_test_read_format_zip_winzip_aes128 (Failed)
	422 - libarchive_test_read_format_zip_winzip_aes256 (Failed)
	424 - libarchive_test_read_format_zip_winzip_aes256_large (Failed)
	435 - libarchive_test_read_append_filter (Failed)
```

Prepare the files for packaging

``` shell
cd out/packaging && \
cp ../build/libarchive/*.a bin && \
cp ../build/libarchive/*.dylib bin && \
cp ../../libarchive/archive{,_entry}.h include/libarchive && \
cp ../../COPYING . && \
cp ../../README.md . && \
cd ../../
```

Run ReMan's packaging tool (or, alternatively, [package without ReMan](#packaging-without-reman))

``` shell
cd out/packaging && \
package ../release libarchive-macos 3.4.3 && \
cd ../../
```

**Note:** Replace `macos` with the target platform (`linux` for Linux, `macos` for macOS, and `win`
for Windows) and `3.4.3` with libarchive's version.

The release packages are stored in `out/release` relative to the current directory.

## Official GHIFARI160 Distribution (for projects mantained by GHIFARI160)

Follow the build and packaging steps for the intended platform as above.

Upload to Spaces in `libarchive/{version}`. Ensure the release packages permissions are set to
public.

**Note:** You **must** use Reman to create the release packages for official GHIFARI160 distribution.

## Packaging without ReMan

Create the Zip release package

``` shell
cd out/packaging && \
zip -r -X ../release/libarchive-macos-v3.4.3.zip . -x "*.git*" && \
tar --exclude="*.git*" -zcvf ../release/libarchive-macos-v3.4.3.tar.gz . && \
tar --exclude="*.git*" -jcvf ../release/libarchive-macos-v3.4.3.tar.bz2 . && \
cd ../../
```

**Note:** Replace `macos` with the target platform (`linux` for Linux, `macos` for macOS, and `win`
for Windows) and `3.4.3` with libarchive's version.
