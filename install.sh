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

    if [ -f $PWD/bin/crashpad ]; then
        rm $PWD/bin/crashpad
    fi
    ln -s $PWD/src/crashpad/crashpad.sh $PWD/bin/crashpad
    
    if [ -f $PWD/bin/packager ]; then
        rm $PWD/bin/packager
    fi
    ln -s $PWD/src/packager/packager.sh $PWD/bin/packager

    echo "Don't forget to add the installation directory to your PATH!"
    echo "Directory: $PWD/bin"
fi
