# Copyright © 2023 R. Scott Gustafson. All rights reserved.

cmake_minimum_required(VERSION 2.11.0)

project(sample)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/angleMachine.cpp 
    ${CMAKE_SOURCE_DIR}/src/angleMachine.h
    ${CMAKE_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_SOURCE_DIR}/src/state.cpp
    ${CMAKE_SOURCE_DIR}/src/state.h
    ${CMAKE_SOURCE_DIR}/src/stateMachine.cpp
    ${CMAKE_SOURCE_DIR}/src/stateMachine.h
    ${CMAKE_SOURCE_DIR}/src/timeMachine.cpp 
    ${CMAKE_SOURCE_DIR}/src/timeMachine.h)

add_executable (sample ${SOURCES})
