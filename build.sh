#!/bin/bash
CPU_NUM=$(grep -c ^processor /proc/cpuinfo)

if [ ! -d build ]; then
    mkdir build
fi
cd build
cmake ..
make VERBOSE=1 -j$CPU_NUM

if [ ! -d bin ]; then
    mkdir bin
fi

DESTDIR=bin make -j$CPU_NUM install
