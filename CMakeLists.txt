cmake_minimum_required(VERSION 2.8)
project(discreture)
set(PROJECT_NAME_STR discreture)

option(BUILD_TESTS "Build gtest unit tests" OFF)
option(BUILD_OLD_TESTS "Build old unit tests" OFF)
option(BUILD_BENCHMARKS "Build benchmarks" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/Discreture)

add_definitions(-march=native -pipe -O3)

message("Installing to " ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*.hpp")



if(BUILD_TESTS)
	find_package(GTest)
	if (GTEST_FOUND)
		find_package(Threads REQUIRED)
		enable_testing()
		include_directories(${GTEST_INCLUDE_DIRS})
		set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
		file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/UTests/*.cpp)
		add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
# 		add_executable(${PROJECT_TEST_NAME} ${PROJECT_SOURCE_DIR}/UTests/combination_tests.cpp ${PROJECT_SOURCE_DIR}/UTests/google_test.cpp)
		target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} Threads::Threads)
		add_test(AllTests ${PROJECT_TEST_NAME})
	else()
		set(BUILD_OLD_TESTS ON)
	endif()
endif (BUILD_TESTS)

if (BUILD_OLD_TESTS)
		message("Google testing framework not found. Falling back to old tests")
		add_executable(testdiscreture 	UTests/OldTests/test_all.cpp 
									UTests/OldTests/combinations_test.cpp 
									UTests/OldTests/dyck_test.cpp 
									UTests/OldTests/misc_test.cpp 
									UTests/OldTests/motzkin_test.cpp 
									UTests/OldTests/multisets_test.cpp
									UTests/OldTests/permutations_test.cpp
									UTests/OldTests/range_test.cpp 
									UTests/OldTests/sequence_test.cpp 
									UTests/OldTests/partitions_test.cpp 
									UTests/OldTests/set_partitions_test.cpp
									UTests/OldTests/numbertheory_tests.cpp)
	endif()

if(BUILD_BENCHMARKS)
	find_package(GSL)
	if (${GSL_FOUND})
		add_definitions(-DTEST_GSL_COMBINATIONS)
		include_directories(${GSL_INCLUDE_DIRS})
	endif()
	add_definitions(-g)
	add_executable(benchmarkdiscreture 	Benchmarks/benchmark_all.cpp 
										Benchmarks/combinations_benchmark.cpp 
										Benchmarks/dyck_benchmark.cpp 
										Benchmarks/misc_benchmark.cpp 
										Benchmarks/motzkin_benchmark.cpp 
										Benchmarks/multisets_benchmark.cpp
										Benchmarks/permutations_benchmark.cpp
										Benchmarks/range_benchmark.cpp 
										Benchmarks/sequence_benchmark.cpp 
										Benchmarks/partitions_benchmark.cpp 
										Benchmarks/set_partitions_benchmark.cpp
										Benchmarks/numbertheory_benchmarks.cpp)
	if (GSL_FOUND)
		target_link_libraries(benchmarkdiscreture ${GSL_LIBRARIES})
	endif()
endif (BUILD_BENCHMARKS)



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
	add_executable(numbertheory examples/numbertheory.cpp)
# 	add_executable(multisets examples/multisets.cpp)
endif (BUILD_EXAMPLES)
