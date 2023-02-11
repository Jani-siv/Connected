cmake_minimum_required(VERSION 3.20)

project(connected)

set(CMAKE_CXX_STANDARD 17)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

if(DEFINED unittest)
    project(unitTests)
    add_subdirectory(${CMAKE_SOURCE_DIR}/DependencyGraph/UnitTests/)
endif()

add_executable(connected main.cpp)
