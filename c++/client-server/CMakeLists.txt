# Copyright © 2020 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

option(BUILD_GMOCK "" OFF)
option(INSTALL_GTEST "" OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/../../thirdparty/googletest/googletest"
                 "${CMAKE_BINARY_DIR}/lib/gtest"
)
# add_subdirectory("${CMAKE_SOURCE_DIR}/../../thirdparty/asio/asio"       
#                  "${CMAKE_BINARY_DIR}/lib/asio"
# )
# add_subdirectory("${CMAKE_SOURCE_DIR}/../../thirdparty/math"       
#                  "${CMAKE_BINARY_DIR}/lib/math"
# )
add_subdirectory("${CMAKE_SOURCE_DIR}/../../thirdparty/boost"       
                 "${CMAKE_BINARY_DIR}/lib/boost"
)

set(SOURCES config.h)

add_executable (sample-client client/main.cpp ${SOURCES})
add_executable (sample-server server/main.cpp server/prime.cpp server/prime.h server/special_functions_prime.h ${SOURCES})
add_executable (sample-test testRunner/primeTest.cpp server/prime.h ${SOURCES})

target_compile_options(sample-test PRIVATE -DTESTING)
target_link_libraries(sample-test PUBLIC gtest gtest_main)