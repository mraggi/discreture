cmake_minimum_required(VERSION 2.8)
project(discreture)

option(BUILD_TESTS "Build unit tests" ON)
option(BUILD_EXAMPLES "Build example programs" ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(CMAKE_CXX_COMPILER clang++)

add_definitions(-Wall)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Discreture)

add_definitions(-Ofast -march=native)

message("Installing to " ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*.hpp")



if(BUILD_TESTS)
	add_executable(testdiscreture 	UTests/test_all.cpp 
									UTests/combinations_test.cpp 
									UTests/dyck_test.cpp 
									UTests/misc_test.cpp 
									UTests/motzkin_test.cpp 
									UTests/multisets_test.cpp
									UTests/permutations_test.cpp
									UTests/range_test.cpp 
									UTests/sequence_test.cpp 
									UTests/partitions_test.cpp 
									UTests/set_partitions_test.cpp)
endif (BUILD_TESTS)

if(BUILD_EXAMPLES)
	add_executable(combinations examples/combinations.cpp)
	add_executable(combinations_reverse examples/combinations_reverse.cpp)
	add_executable(combinations_tree examples/combinations_tree.cpp)
	add_executable(combinations_tree_reverse examples/combinations_tree_reverse.cpp)
	add_executable(dyck examples/dyck.cpp)
	add_executable(motzkin examples/motzkin.cpp)
	add_executable(permutations examples/permutations.cpp)
# 	add_executable(range examples/range.cpp)
	add_executable(setpartitions examples/setpartitions.cpp)
	add_executable(partitions examples/partitions.cpp)
# 	add_executable(multisets examples/multisets.cpp)
endif (BUILD_EXAMPLES)
