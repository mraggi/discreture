
cmake_minimum_required(VERSION 3.0)

##
## PROJECT
## name and version
project(discreture_examples LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Threads)

set(RELEASE_COMPILE_FLAGS "-Ofast -DNDEBUG -ffast-math")
set(DEBUG_COMPILE_FLAGS "-g -O1 -Wall -Wextra -Wpedantic -Wno-unused -Wno-sign-compare")

function(build_example TEST_SRC)
	get_filename_component(test_src_we ${TEST_SRC} NAME_WE)
	set(target "${test_src_we}")
	add_executable(${target} ${TEST_SRC})
	target_link_libraries(
		${target}
		discreture::discreture
	)
# 	target_compile_options(
# 		${target}
# 		PRIVATE
# 		$<$<CONFIG:Debug>:${DEBUG_COMPILE_FLAGS}>
# 		$<$<CONFIG:Release>:${RELEASE_COMPILE_FLAGS}>
# 	)
endfunction(build_example)

set(
	TEST_SRCS
	combinations.cpp
	combinations_reverse.cpp
	lex_combinations.cpp
	lex_combinations_reverse.cpp
	dyck.cpp
	motzkin.cpp
	permutations.cpp
	arithmetic_progression.cpp
	setpartitions.cpp
	partitions.cpp
	partitions_reverse.cpp
	multisets.cpp
	playground.cpp
	tutorial.cpp
)

foreach(test_src ${TEST_SRCS})
	build_example(${test_src})
endforeach(test_src)

if (${CMAKE_USE_PTHREADS_INIT})
    add_executable(tutorial_parallel tutorial_parallel.cpp)
    target_link_libraries(
		tutorial_parallel
		discreture::discreture
	)
    target_link_libraries(tutorial_parallel ${CMAKE_THREAD_LIBS_INIT})
endif()
