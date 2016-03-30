cmake_minimum_required(VERSION 2.8)
project(discreture)

option(BUILD_TESTS "Build test programs" ON) # Probably should leave it like this

# Set to ON in order to compile with clang instead of GCC. According to tests, 
# Clang is faster for: 
#	Combinations, 
#	Partitions, 
#	Dyck Paths 
#	Motzkin Paths. 
#
# GCC is faster for: 
#	subsets 
#	permutations.
#   Set Partitions
#
# See readme for more details and actual benchmarks. If you really want speed, though, 
# you probably want to test on your own, since usually the bottleneck will be your own code
 
option(USE_CLANG "Use CLANG to build" OFF)

if (USE_CLANG)
	SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
	SET (CMAKE_AR      		"/usr/bin/llvm-ar")
	SET (CMAKE_LINKER  		"/usr/bin/llvm-ld")
	SET (CMAKE_NM      		"/usr/bin/llvm-nm")
	SET (CMAKE_OBJDUMP 		"/usr/bin/llvm-objdump") 
	SET (CMAKE_RANLIB  		"/usr/bin/llvm-ranlib")
endif (USE_CLANG)    

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(BUILD_SHARED_LIBS ON)

add_definitions(-std=c++14)
add_definitions(-Ofast -march=native)
add_definitions(-DNDEBUG)
# add_definitions(-Wall -Weffc++ -Wpedantic -Werror)

link_directories (${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})
 
add_library(discreture SHARED Misc.cpp Sequences.cpp Subsets.cpp Vectorhelpers.cpp Probability.cpp)
# message ("Installing to " ${CMAKE_INSTALL_PREFIX})
# install (TARGETS discreture DESTINATION lib)
# install(DIRECTORY . DESTINATION include
#         FILES_MATCHING PATTERN "*.hpp")

if(BUILD_TESTS)
	add_executable(testdiscreture main.cpp Tests.cpp)
	target_link_libraries(testdiscreture discreture)
# 	install (TARGETS testdiscreture DESTINATION ${PROJECT_BINARY_DIR})
endif (BUILD_TESTS)
