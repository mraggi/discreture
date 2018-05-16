cmake_minimum_required(VERSION 3.2)

project(discreture)
enable_language(C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_BENCHMARKS "Build benchmarks" OFF)
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_OLD_TESTS "Build old unit tests" OFF)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "coverage")
    set(BUILD_TESTS ON)
endif()

find_package(Boost REQUIRED)

# Set version number (change as needed). These definitions are available
# by including "exampleConfig.h" in the source. 
# See exampleConfig.h.in for some more details.
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 2)


# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)


# --------------------------------------------------------------------------------
#                          Compile flags (change as needed).
# --------------------------------------------------------------------------------
# Set the C++ standard you wish to use (will apply to all files).
# If you do not use any features that limits the standard required,
# you could omit this line.
set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Things to always include as flags. Change as needed.
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")  

# Build-type specific flags. Change as needed.
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")

message(STATUS "Building with the following extra flags: ${CMAKE_CXX_FLAGS}")

# --------------------------------------------------------------------------------
#                         Locate files
# --------------------------------------------------------------------------------
# We make sure that CMake sees all the files.
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/Discreture
    ${PROJECT_SOURCE_DIR}/external/googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/include)



# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------
# Add a make target 'gtest', that runs the tests (and builds all dependencies).
# The setup of Google Test is done at the very end of this file.


if(${BUILD_TESTS})
    find_package(Threads REQUIRED)
    file(GLOB TESTFILES "tests/*.cpp")
    set(TEST_MAIN unit_tests.x)
    add_executable(${TEST_MAIN} ${TESTFILES})
    add_dependencies(${TEST_MAIN} googletest)
    target_link_libraries(${TEST_MAIN} googletest Threads::Threads)
    add_custom_target(gtest COMMAND "${PROJECT_BINARY_DIR}/${TEST_MAIN}" DEPENDS ${TEST_MAIN})

    # Add a standard make target 'test' that runs the tests under CTest (only as an alt. to gtest).
    include(CTest)
    enable_testing()
    add_test(unit_tests ${PROJECT_BINARY_DIR}/${TEST_MAIN})
endif()

if (${BUILD_OLD_TESTS})
	file(GLOB OLD_TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/OldTests/*.cpp)
	add_executable(discreture_test_old ${OLD_TEST_SRC_FILES})
endif()


# --------------------------------------------------------------------------------
#                            Build!
# --------------------------------------------------------------------------------
if(${BUILD_EXAMPLES})
	add_executable(combinations examples/combinations.cpp)
	add_executable(combinations_reverse examples/combinations_reverse.cpp)
	add_executable(combinations_tree examples/combinations_tree.cpp)
	add_executable(combinations_tree_reverse examples/combinations_tree_reverse.cpp)
	add_executable(dyck examples/dyck.cpp)
	add_executable(motzkin examples/motzkin.cpp)
	add_executable(permutations examples/permutations.cpp)
	add_executable(number_range examples/number_range.cpp)
	add_executable(setpartitions examples/setpartitions.cpp)
	add_executable(partitions examples/partitions.cpp)
	add_executable(partitions_reverse examples/partitions_reverse.cpp)
	add_executable(multisets examples/multisets.cpp)
endif()

if(BUILD_BENCHMARKS)
	find_package(GSL)
	if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		add_definitions("-mtune=native")
	endif()
	if (${GSL_FOUND})
		add_definitions(-DTEST_GSL_COMBINATIONS)
		include_directories(${GSL_INCLUDE_DIRS})
	endif()
	file(GLOB BENCHMARK_SRC_FILES ${PROJECT_SOURCE_DIR}/benchmarks/*.cpp)
	add_executable(discreture_benchmark ${BENCHMARK_SRC_FILES})
	if (GSL_FOUND)
		target_link_libraries(discreture_benchmark ${GSL_LIBRARIES})
	endif()
endif()

if(${BUILD_OLD_BENCHMARKS})
	find_package(GSL)
	if (${GSL_FOUND})
		add_definitions(-DTEST_GSL_COMBINATIONS)
		include_directories(${GSL_INCLUDE_DIRS})
	endif(${GSL_FOUND})
	file(GLOB OLD_BENCHMARK_SRC_FILES ${PROJECT_SOURCE_DIR}/Benchmarks/old/*.cpp)
	add_executable(discreture_benchmark_old ${OLD_BENCHMARK_SRC_FILES})
	if (GSL_FOUND)
		target_link_libraries(discreture_benchmark_old ${GSL_LIBRARIES})
	endif(GSL_FOUND)
endif()




# --------------------------------------------------------------------------------
#                         Code Coverage (no change needed).
# --------------------------------------------------------------------------------
# If CMake aborts due to missing dependencies for code coverage 
# (gcov, lcov, genhtml and supported compiler), comment this line.
include(CodeCoverage)

# --------------------------------------------------------------------------------
#                         Documentation (no change needed).
# --------------------------------------------------------------------------------
# Add a make target 'doc' to generate API documentation with Doxygen.
# You should set options to your liking in the file 'Doxyfile.in'.
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc 
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile &> doxygen.log
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "${BoldMagenta}Generating API documentation with Doxygen (open ./html/index.html to view).${ColourReset}" VERBATIM
        )
endif(DOXYGEN_FOUND)


# --------------------------------------------------------------------------------
#                         Google Test (no change needed).
# --------------------------------------------------------------------------------
# The following makes sure that an up-to-date version of googletest is available,
# and built so that it may be used by your tests. 
add_custom_target( git_update
    COMMAND git submodule init
    COMMAND git submodule update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
add_library( googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc )
add_dependencies(googletest git_update)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc  PROPERTIES GENERATED 1)
set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc PROPERTIES GENERATED 1)



# --------------------------------------------------------------------------------
#                            Misc (no change needed).
# --------------------------------------------------------------------------------
# Have CMake parse the config file, generating the config header, with
# correct definitions. Here only used to make version number available to
# the source code. Include "exampleConfig.h" (no .in suffix) in the source.

# configure_file ("${PROJECT_SOURCE_DIR}/include/exampleConfig.h.in" "${PROJECT_BINARY_DIR}/exampleConfig.h")

# add the binary tree to the search path for include files
# so that we will find exampleConfig.h
# include_directories("${PROJECT_BINARY_DIR}")

# Ask CMake to output a compile_commands.json file for use with things like Vim YCM.
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
