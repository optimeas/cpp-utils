project(cpp-utils-tests)

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES
    scope_guard_tests.cpp
    hexdump_tests.cpp
    stringutils_tests.cpp
    base64_tests.cpp
    timedthresholdcounter_tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
    cpp-utils
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})

