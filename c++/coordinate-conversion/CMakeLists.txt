# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/csv.cpp 
	${CMAKE_SOURCE_DIR}/src/csv.h 
	${CMAKE_SOURCE_DIR}/src/coord.h 
	${CMAKE_SOURCE_DIR}/src/coord.cpp)

add_executable (sample ${CMAKE_SOURCE_DIR}/src/main.cpp ${SOURCES})
add_executable (sample-test ${SOURCES})

target_compile_options(sample-test PRIVATE -DTESTING)
target_link_libraries(sample-test PUBLIC gtest gtest_main)
