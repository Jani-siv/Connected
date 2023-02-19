set(BASEPATH "${CMAKE_SOURCE_DIR}")
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


set(TESTNAME JsonTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/lib/json/json.cpp
        ${CMAKE_SOURCE_DIR}/lib/json/UnitTests/jsonTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)