
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

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(
        benchmark_discreture
        PRIVATE "-mtune=native" "-Ofast"
    )
    message("Using compiler: " ${CMAKE_CXX_COMPILER_ID})
endif()

find_package(GSL)

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
find_package(Threads)
if (${CMAKE_USE_PTHREADS_INIT})
    add_executable(
        benchmark_parallel 
        parallel/parallel_benchmarks.cpp)
    target_link_libraries(
        benchmark_parallel 
        PRIVATE ${CMAKE_THREAD_LIBS_INIT})
endif()
