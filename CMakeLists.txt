cmake_minimum_required(VERSION 3.0)

project(discreture)
enable_language(C CXX)

if (NOT CMAKE_BUILD_TYPE)
    message("CMAKE_BUILD_TYPE not specified! Setting to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_BENCHMARKS "Build benchmarks" OFF)
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_OWN_GOOGLETEST "Build own google's unit testing framework, even if found" OFF)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "coverage")
    set(BUILD_TESTS ON)
endif()

find_package(Boost REQUIRED)
find_package(Threads)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 7)


# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)

set(CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Build-type specific flags. Change as needed.
message("Compiler used: " ${CMAKE_CXX_COMPILER_ID})
if (MSVC)
# 	message("Using msvc")
else()
# 	message("Not using MSVC")
	SET(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG -ffast-math")
	SET(CMAKE_CXX_FLAGS_DEBUG "-g -O1 -Wall -Wextra -Wpedantic -Wno-unused -Wno-sign-compare")
	if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
		message("Extra flags for RELEASE: " ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE})
	else()
		message("Extra flags for DEBUG: "  ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})		
	endif()
endif() # Help wanted: what to do if MSVC? Does it compile? I have no idea and no way to test!

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/googletest
    ${PROJECT_SOURCE_DIR}/external/googletest/include)



if(${BUILD_TESTS})
    find_package(GTest)
    find_package(Threads REQUIRED)
    set(TEST_LIB googletest)
    set(TEST_FILES  tests/main.cpp
                    tests/sequence_tests.cpp
                    tests/integer_interval_tests.cpp
                    tests/arithmetic_progression_tests.cpp
                    tests/combination_tests.cpp
                    tests/lex_combinations_tests.cpp
                    tests/permutation_tests.cpp
                    tests/multiset_tests.cpp
                    tests/dyck_tests.cpp
                    tests/motzkin_tests.cpp
                    tests/partition_tests.cpp
                    tests/set_partition_tests.cpp
                    tests/idxview_tests.cpp
                    tests/idxview_container_tests.cpp
                    tests/reversed_tests.cpp
        )
    set(TEST_MAIN unit_tests.x)
	if (${GTEST_FOUND} AND NOT ${BUILD_OWN_GOOGLETEST})
        include_directories(${GTEST_INCLUDE_DIRS})
        set(TEST_LIB ${GTEST_BOTH_LIBRARIES})
        add_executable(${TEST_MAIN} ${TEST_FILES})
	else()
		message("Google testing framework not found. Building our own!")
        add_custom_target( git_update
        COMMAND git submodule init
        COMMAND git submodule update
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} )
        add_library(googletest
            ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc
            ${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc)
        add_dependencies(googletest git_update)
        set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest-all.cc  PROPERTIES GENERATED 1)
        set_source_files_properties(${PROJECT_SOURCE_DIR}/external/googletest/src/gtest_main.cc PROPERTIES GENERATED 1)
        add_executable(${TEST_MAIN} ${TEST_FILES})
        add_dependencies(${TEST_MAIN} ${TEST_LIB})
    endif()
    
    target_link_libraries(${TEST_MAIN} ${TEST_LIB} ${CMAKE_THREAD_LIBS_INIT})
    add_custom_target(gtest COMMAND "${PROJECT_BINARY_DIR}/${TEST_MAIN}" DEPENDS ${TEST_MAIN})

    # Add a standard make target 'test' that runs the tests under CTest (only as an alt. to gtest).
    include(CTest)
    enable_testing()
    add_test(unit_tests ${PROJECT_BINARY_DIR}/${TEST_MAIN})
endif()


# --------------------------------------------------------------------------------
#                            Build!
# --------------------------------------------------------------------------------
if(${BUILD_EXAMPLES})
	add_executable(combinations examples/combinations.cpp)
	add_executable(combinations_reverse examples/combinations_reverse.cpp)
	add_executable(lex_combinations examples/lex_combinations.cpp)
	add_executable(lex_combinations_reverse examples/lex_combinations_reverse.cpp)
	add_executable(dyck examples/dyck.cpp)
	add_executable(motzkin examples/motzkin.cpp)
	add_executable(permutations examples/permutations.cpp)
	add_executable(arithmetic_progression examples/arithmetic_progression.cpp)
	add_executable(setpartitions examples/setpartitions.cpp)
	add_executable(partitions examples/partitions.cpp)
	add_executable(partitions_reverse examples/partitions_reverse.cpp)
	add_executable(multisets examples/multisets.cpp)
	add_executable(playground examples/playground.cpp)
	add_executable(tutorial examples/tutorial.cpp)
    if (${CMAKE_USE_PTHREADS_INIT})
        add_executable(tutorial_parallel examples/tutorial_parallel.cpp)
        target_link_libraries(tutorial_parallel ${CMAKE_THREAD_LIBS_INIT})
	endif()
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
	add_executable(benchmark_discreture benchmarks/main.cpp
                                        benchmarks/combs.cpp
                                        benchmarks/perms.cpp
                                        benchmarks/multisets.cpp
                                        benchmarks/dyckmotzkin.cpp
                                        benchmarks/partitions.cpp
                                        )
    if (GSL_FOUND)
		target_link_libraries(benchmark_discreture ${GSL_LIBRARIES})
	endif()
    
    if (${CMAKE_USE_PTHREADS_INIT})
        add_executable(benchmark_parallel benchmarks/parallel/parallel_benchmarks.cpp)
        target_link_libraries(benchmark_parallel ${CMAKE_THREAD_LIBS_INIT})
	endif()

	
endif()

include(CodeCoverage)

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
