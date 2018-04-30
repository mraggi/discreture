#!/bin/bash

rm -rf ct-build
mkdir ct-build
cd ct-build
cmake -DBUILD_BENCHMARKS=ON -DBUILD_EXAMPLES=ON -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;--header-filter=.*;-fix;-checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements,-fuchsia-*,-hicpp-braces-around-statements,-llvm-header-guard,-misc-unused-parameters,-google-runtime-references" ..
make
