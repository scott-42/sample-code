# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_GMOCK "" OFF)
option(INSTALL_GTEST "" OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/../../thirdparty/googletest/googletest"
                 "${CMAKE_BINARY_DIR}/lib"
)

set(SOURCES csv.cpp csv.h coord.h coord.cpp)

add_executable (sample main.cpp ${SOURCES})
add_executable (sample-test ${SOURCES})

target_compile_options(sample-test PRIVATE -DTESTING)
target_link_libraries(sample-test PUBLIC gtest gtest_main)