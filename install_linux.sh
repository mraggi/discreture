#!/bin/bash
mkdir build
cd build
cmake ..
make
sudo cp libdiscreture.so /usr/lib
sudo mkdir /usr/include/discreture
cd ..
sudo cp *.hpp /usr/include/discreture/
