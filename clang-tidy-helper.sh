#!/bin/bash

rm -rf ct-build
mkdir ct-build
cd ct-build
# cmake -DBUILD_TESTS=ON -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;--fix;-checks=*,-google-build-using-namespace,-google-readability-braces-around-statements,-readability-braces-around-statements" ..
cmake -DBUILD_BENCHMARKS=ON -DBUILD_EXAMPLES=ON -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_CLANG_TIDY:STRING="clang-tidy;--fix;-checks=*,-google-readability-braces-around-statements,-readability-braces-around-statements" ..
make
