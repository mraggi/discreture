#!/bin/bash

rm -rf build-clang-tidy
mkdir build-clang-tidy
cd build-clang-tidy

cmake -DBUILD_TESTS=OFF -DBUILD_BENCHMARKS=ON -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;--header-filter=.*;-checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements,-fuchsia-*,-hicpp-braces-around-statements,-llvm-header-guard,-misc-unused-parameters,-google-runtime-references,-google-runtime-int,-hicpp-explicit-conversions" ..
make
