#!/bin/bash

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [ $machine == "Linux" ] || [ $machine == "Mac" ]; then
    
    if ! [ -d $PWD/bin ]; then
        mkdir -p bin
    fi

    if [ -f $PWD/bin/build-crashpad ]; then
        rm $PWD/bin/build-crashpad
    fi
    ln -s $PWD/src/crashpad/crashpad.sh $PWD/bin/build-crashpad

    if [ -f $PWD/bin/gencontainer-crashpad ]; then
        rm $PWD/bin/gencontainer-crashpad
    fi
    ln -s $PWD/src/crashpad/generate-container.sh $PWD/bin/gencontainer-crashpad
    
    if [ -f $PWD/bin/package ]; then
        rm $PWD/bin/package
    fi
    ln -s $PWD/src/packager/packager.sh $PWD/bin/package

    echo "Don't forget to add the installation directory to your PATH!"
    echo "Directory: $PWD/bin"
    echo "Set REMAN_DIR=$PWD"
fi
