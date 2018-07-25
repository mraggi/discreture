#!/bin/bash

rm -rf build-cppcheck
mkdir build-cppcheck
cd build-cppcheck

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_BENCHMARKS=ON ..
echo -e "---------------\n"
sed -i 's/tutorial\.cpp/tutorial_parallel\.cpp/g' compile_commands.json
cppcheck --project=compile_commands.json --enable=all -i /home/mraggi/Dropbox/sources/Mathematics/discreture/examples/tutorial.cpp
cd ..
