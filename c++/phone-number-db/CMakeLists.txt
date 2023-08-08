# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/sample.cpp 
    ${CMAKE_SOURCE_DIR}/src/database.cpp 
    ${CMAKE_SOURCE_DIR}/src/database.h 
    ${CMAKE_SOURCE_DIR}/src/phoneNumber.cpp 
    ${CMAKE_SOURCE_DIR}/src/phoneNumber.h)
set(TESTS ${CMAKE_SOURCE_DIR}/src/database_test.cpp ${CMAKE_SOURCE_DIR}/src/phoneNumber_test.cpp)

add_executable (sample ${SOURCES})
add_executable (sample-test ${SOURCES} ${TESTS})

target_compile_options(sample-test PRIVATE -DTEST)
target_link_libraries(sample-test PUBLIC cppunit)