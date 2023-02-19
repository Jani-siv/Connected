cmake_minimum_required(VERSION 3.20)

project(connected)

set(CMAKE_CXX_STANDARD 17)

set(BASEPATH "${CMAKE_SOURCE_DIR}")

add_library(json SHARED)
target_include_directories(json PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory(lib/json)


if(DEFINED unittest)
    project(unitTests)
    add_subdirectory(${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/)
    add_subdirectory(${CMAKE_SOURCE_DIR}/lib/json/UnitTests/)
endif()

add_executable(connected main.cpp)
target_link_libraries(connected PRIVATE json)

