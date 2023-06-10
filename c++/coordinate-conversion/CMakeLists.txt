# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(scitec-sample)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_GMOCK "" OFF)
option(INSTALL_GTEST "" OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty/googletest"
                 "${CMAKE_BINARY_DIR}/lib"
)

set(SOURCES csv.cpp csv.h coord.h coord.cpp)

add_executable (scitec-sample main.cpp ${SOURCES})
add_executable (scitec-sample-test ${SOURCES})

target_compile_options(scitec-sample-test PRIVATE -DTESTING)
target_link_libraries(scitec-sample-test PUBLIC gtest gtest_main)