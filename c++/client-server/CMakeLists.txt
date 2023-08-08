# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES 
    ${CMAKE_SOURCE_DIR}/src/config.h)

add_executable (sample-client 
    ${CMAKE_SOURCE_DIR}/src/main-client.cpp 
    ${SOURCES})
add_executable (sample-server 
    ${CMAKE_SOURCE_DIR}/src/main-server.cpp 
    ${CMAKE_SOURCE_DIR}/src/prime.cpp 
    ${CMAKE_SOURCE_DIR}/src/prime.h 
    ${CMAKE_SOURCE_DIR}/src/special_functions_prime.h 
    ${SOURCES})
add_executable (sample-test 
    ${CMAKE_SOURCE_DIR}/src/primeTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/prime.cpp 
    ${CMAKE_SOURCE_DIR}/src/prime.h 
    ${SOURCES})

target_compile_options(sample-server PRIVATE -DBOOST_ALL_NO_LIB=1)
target_link_libraries(sample-server PUBLIC boost_context boost_coroutine)

target_compile_options(sample-client PRIVATE -DBOOST_ALL_NO_LIB=1)
target_link_libraries(sample-client PUBLIC boost_context boost_coroutine)

target_compile_options(sample-test PRIVATE -DTESTING)
target_link_libraries(sample-test PUBLIC gtest gtest_main)