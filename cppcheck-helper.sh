#!/bin/bash

rm -rf build-cppcheck
mkdir build-cppcheck
cd build-cppcheck

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
echo -e "---------------\n"

cppcheck --project=compile_commands.json --enable=all > cppcheckoutput.txt
cd ..
