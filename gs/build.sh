#!/bin/bash
cd `dirname $0`
cd src
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && make
