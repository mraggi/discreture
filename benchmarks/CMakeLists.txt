
cmake_minimum_required(VERSION 3.0)

##
## PROJECT
## name and version
project(discreture_benchmarks LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(
    benchmark_discreture 
    main.cpp
    combs.cpp
    perms.cpp
    multisets.cpp
    dyckmotzkin.cpp
    partitions.cpp
)

target_link_libraries(
    benchmark_discreture 
    PRIVATE discreture::discreture
)

find_package(GSL)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(
        benchmark_discreture
        PRIVATE "-mtune=native"
    )
endif()

if (GSL_FOUND)

    target_compile_definitions(
        benchmark_discreture
        PRIVATE "-DTEST_GSL_COMBINATIONS"
    )

    target_include_directories(
        benchmark_discreture
        PRIVATE ${GSL_INCLUDE_DIRS}
    )

	target_link_libraries(
        benchmark_discreture 
        PRIVATE ${GSL_LIBRARIES}
    )

endif()

if (${CMAKE_USE_PTHREADS_INIT})
    add_executable(
        benchmark_parallel 
        benchmarks/parallel/parallel_benchmarks.cpp)
    target_link_libraries(
        benchmark_parallel 
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()
