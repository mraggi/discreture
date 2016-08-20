cmake_minimum_required(VERSION 2.8)
project(discreture)

option(BUILD_TESTS "Build test programs" ON) # Probably should leave it like this
option(USE_CLANG "Use CLANG to build" OFF)


set(CMAKE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_BINARY_DIR ${CMAKE_LIBRARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)
set(BUILD_SHARED_LIBS ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Discreture)

if (USE_CLANG)
	SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
	SET (CMAKE_AR      		"/usr/bin/llvm-ar")
	SET (CMAKE_LINKER  		"/usr/bin/llvm-ld")
	SET (CMAKE_NM      		"/usr/bin/llvm-nm")
	SET (CMAKE_OBJDUMP 		"/usr/bin/llvm-objdump") 
	SET (CMAKE_RANLIB  		"/usr/bin/llvm-ranlib")
endif (USE_CLANG)

add_definitions(-std=c++14)
add_definitions(-Ofast -march=native)
# add_definitions(-Wall -Weffc++ -Wpedantic -Werror)

add_library(discreture SHARED Sequences.cpp Subsets.cpp Vectorhelpers.cpp Probability.cpp)
message("Installing to " ${CMAKE_INSTALL_PREFIX})
install(TARGETS discreture LIBRARY DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*.hpp")

if(BUILD_TESTS)
	add_executable(testdiscreture main.cpp Tests.cpp)
	target_link_libraries(testdiscreture discreture)
endif (BUILD_TESTS)
