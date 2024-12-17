#!/bin/sh
mkdir -p cmake-build
cd cmake-build
cmake .. -G "Unix Makefiles"
make
yes | cp ./StuInfo-Manager ..
cd ..
rm -rf cmake-build
