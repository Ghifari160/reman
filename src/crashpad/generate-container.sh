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
    rm Dockerfile
fi
cp $REMAN_DIR/src/crashpad/Dockerfile Dockerfile

docker build --tag build .

echo "Successfully built a local dev container (tagged as build)."
