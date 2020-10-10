#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo "Packaging..."

mkdir -p ${1}

if [ $machine == "Linux" ]; then
    zip -r -X "${1}/${2}-v${3}.zip" . -x "*.git*"
    tar --exclude="*.git*" -zcvf "${1}/${2}-v${3}.tar.gz" .
    tar --exclude="*.git*" -jcvf "${1}/${2}-v${3}.tar.bz2" .
elif [ $machine == "Mac" ]; then
    zip -r -X "${1}/${2}-v${3}.zip" . -x "*.git*" "*.DS_Store"
    tar --exclude="*.git*" --exclude="*.DS_Store" -zcvf "${1}/${2}-v${3}.tar.gz" .
    tar --exclude="*.git*" --exclude="*.DS_Store" -jcvf "${1}/${2}-v${3}.tar.bz2" .
fi
