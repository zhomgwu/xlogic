#!/bin/bash

cd `dirname $0`

# libevent
cd libevent-2.1.8-stable
./configure --prefix=.. && make
cd ..

# yaml-cpp
cd yaml-cpp
mkdir build
cd build
cmake .. && make
cd ../..
