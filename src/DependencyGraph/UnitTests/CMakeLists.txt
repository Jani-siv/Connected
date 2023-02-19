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


set(TESTNAME DependencyGraphTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/DependencyGraph.cpp
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/DependencyGraphTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main json)
add_test(${TESTNAME} ${TESTNAME}Tests)

set(TESTNAME ObjectClassTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/ObjectClass.cpp
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/ObjectClassTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main json)
add_test(${TESTNAME} ${TESTNAME}Tests)

set(TESTNAME EntityParserTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/EntityParser.cpp
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/EntityParserTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main json)
add_test(${TESTNAME} ${TESTNAME}Tests)

set(TESTNAME EntityCreatorTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/EntityCreator.cpp
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/EntityCreatorTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main json)
add_test(${TESTNAME} ${TESTNAME}Tests)

set(TESTNAME CmakeParserTests)
project(${TESTNAME})

set(SOURCEFILES
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/CmakeParser.cpp
        ${CMAKE_SOURCE_DIR}/src/DependencyGraph/UnitTests/CmakeParserTests.cpp
        )

enable_testing()

add_executable(
        ${TESTNAME}
        ${SOURCEFILES}
)
target_link_libraries(${TESTNAME} gtest gmock gtest_main)
add_test(${TESTNAME} ${TESTNAME}Tests)