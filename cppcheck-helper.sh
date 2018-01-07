#!/bin/bash

rm -rf cppcheck-build
mkdir cppcheck-build
cd cppcheck-build

cmake -DBUILD_BENCHMARKS=ON -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
echo -e "---------------\n"

cppcheck --project=compile_commands.json --enable=all > cppcheckoutput.txt
