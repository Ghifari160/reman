#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [ -f Dockerfile ]; then
    mv Dockerfile Dockerfile.remanbak
fi
cp $REMAN_DIR/src/crashpad/Dockerfile Dockerfile

docker build --tag build .

rm Dockerfile

if [ -f Dockerfile.remanbak ]; then
    mv Dockerfile.remanbak Dockerfile
fi

echo "Successfully built a local dev container (tagged as build)."
