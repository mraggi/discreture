
cmake_minimum_required(VERSION 3.0)

##
## PROJECT
## name and version
project(discreture_tests LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Threads REQUIRED)

set(RELEASE_COMPILE_FLAGS "-Ofast -DNDEBUG -ffast-math")
set(DEBUG_COMPILE_FLAGS "-g -O1 -Wall -Wextra -Wpedantic -Wno-unused -Wno-sign-compare")

add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest "external/googletest")

set(TEST_FILES
	main.cpp
    sequence_tests.cpp
    integer_interval_tests.cpp
    arithmetic_progression_tests.cpp
    combination_tests.cpp
    lex_combinations_tests.cpp
    permutation_tests.cpp
    multiset_tests.cpp
    dyck_tests.cpp
    motzkin_tests.cpp
    partition_tests.cpp
    set_partition_tests.cpp
    idxview_tests.cpp
    idxview_container_tests.cpp
    reversed_tests.cpp
)

set(TEST_MAIN unit_tests.x)
add_executable(${TEST_MAIN} ${TEST_FILES})

target_link_libraries(
        ${target}
        ${CMAKE_THREAD_LIBS_INIT}
        discreture::discreture
        gtest
        gmock
        gtest_main
    )

message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

# function(build_test SRC_FILE)
#     get_filename_component(src_name_we ${SRC_FILE} NAME_WE)
#     set(target "${src_name_we}")
#     add_executable(${target} ${SRC_FILE})
#     add_dependencies(${target} gtest)
#     target_link_libraries(
#         ${target}
#         ${CMAKE_THREAD_LIBS_INIT}
#         discreture::discreture
#         gtest
#         gmock
#         gtest_main
#     )
#     target_compile_options(
#         ${target}
#         PRIVATE
#         $<$<CONFIG:Debug>:${DEBUG_COMPILE_FLAGS}>
#         $<$<CONFIG:Release>:${RELEASE_COMPILE_FLAGS}>
#     )
#     add_test(${target} ${target})
# endfunction(build_test)
# 
# foreach(test_src ${TEST_FILES})
#     build_test(${test_src})
# endforeach(test_src)
# 
# Add a standard make target 'test' that runs the tests under CTest (only as an alt. to gtest).
# include(CTest)
# add_test(unit_tests ${PROJECT_BINARY_DIR}/${TEST_MAIN})
