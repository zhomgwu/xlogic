#!/bin/bash
cd `dirname $0`

if [ ! -d lib ]; then
    mkdir lib
fi
# libevent
cd libevent-2.1.8-stable
chmod +x ./configure
./configure && make
cp .libs/*.a ../lib
cp .libs/*.so* ../lib
cd ..

# yaml-cpp
cd yaml-cpp
if [ ! -d build ]; then
    mkdir build
fi
cd build
cmake .. && make
cp *.a ../../lib
cp *.so* ../../lib
cd ../..
