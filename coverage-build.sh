#!/bin/bash

rm -rf build-cov
mkdir build-cov
cd build-cov
export CXX=g++
export CC=gcc
cmake .. -DCMAKE_BUILD_TYPE=Coverage
make
make coverage
#firefox ./coverage_out/index.html
