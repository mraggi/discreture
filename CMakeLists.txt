cmake_minimum_required(VERSION 3.0)

##
## PROJECT
## name and version
project(discreture VERSION 1.9 LANGUAGES CXX)

##
## OPTIONS
##
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_BENCHMARKS "Build benchmarks" OFF)
option(BUILD_TESTS "Build unit tests" OFF)


##
## INCLUDE
##
##
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
include(ExternalProject)


string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "coverage")
	include(CodeCoverage)
endif()

include(ConfigSafeGuards)
include(Colors)

##
## CONFIGURATION
##
set(DISCRETURE_TARGET_NAME              ${PROJECT_NAME})
set(DISCRETURE_TARGETS_EXPORT_NAME      "${PROJECT_NAME}Targets")
set(DISCRETURE_CMAKE_CONFIG_DIR         "${CMAKE_CURRENT_BINARY_DIR}")
set(DISCRETURE_CMAKE_PROJECT_TARGETS_FILE       "${DISCRETURE_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")

##
## TARGET
## create target and add include path
##
add_library(${DISCRETURE_TARGET_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${DISCRETURE_TARGET_NAME} ALIAS ${DISCRETURE_TARGET_NAME})

find_package(Boost REQUIRED)

target_include_directories(
    ${DISCRETURE_TARGET_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(
    ${DISCRETURE_TARGET_NAME}
    INTERFACE
    cxx_std_14
)

string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (cmake_build_type_tolower STREQUAL "coverage")
    set(BUILD_TESTS ON)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()


##
## INSTALL
## create target and add include path
##
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_PREFIX}/include/)
export(
    TARGETS     ${DISCRETURE_TARGET_NAME}
    NAMESPACE   ${PROJECT_NAME}::
    FILE        ${DISCRETURE_CMAKE_PROJECT_TARGETS_FILE}
)

