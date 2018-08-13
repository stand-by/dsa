#!/bin/bash

cd ./build
cmake ..
make
make install
# cmake -G Xcode ..
cd ../.
