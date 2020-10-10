#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo "Building crashpad"

gn gen out/Default
ninja -C out/Default

mkdir -p out/Packaging/bin out/Packaging/include out/Packaging/lib

echo "Copying compiled binaries"

cp out/Default/crashpad_database_util out/Packaging/bin/crashpad_database_util
cp out/Default/crashpad_handler out/Packaging/bin/crashpad_handler
cp out/Default/crashpad_http_upload out/Packaging/bin/crashpad_http_upload

echo "Copying header files"

if [ ! command -v rsync &> /dev/null ]; then
    if [ $machine == "Linux" ]; then
        echo "Rsync not found on Linux. Copying with cp"
        find . -name \*.h -exec cp --parent {} out/Packaging/include \;
    elif [ $machine == "Mac" ]; then
        echo "Rsync not found on macOS. Unable to copy header files"
        exit 1
    fi
else
    find . -type f \( -iname "*.h" ! -path "./out/*" \) -exec rsync -R {} out/Packaging/include \;
fi

echo "Copying libraries"

cp out/Default/obj/third_party/mini_chromium/mini_chromium/base/libbase.a out/Packaging/lib/libbase.a
cp out/Default/obj/client/libclient.a out/Packaging/lib/libclient.a
cp out/Default/obj/util/libutil.a out/Packaging/lib/libutil.a

cd out/Packaging

${PACKAGER} ${PACKAGER_TARGET} ${PACKAGER_PROJECT} ${PACKAGER_PROJECT_VERSION}
