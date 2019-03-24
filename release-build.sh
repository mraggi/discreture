#!/bin/bash

rm -rf build
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_BENCHMARKS=ON ..
make
