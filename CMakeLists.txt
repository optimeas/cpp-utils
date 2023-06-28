project(cpp-utils)

set(HEADERS
    include/cpp-utils/logging.hpp
    include/cpp-utils/loggingstdout.hpp
    include/cpp-utils/monitor.hpp
    include/cpp-utils/pimpl_ptr.hpp
    include/cpp-utils/scope_guard.hpp
    include/cpp-utils/hexdump.hpp
    include/cpp-utils/stringutils.hpp
    include/cpp-utils/base64.hpp
    include/cpp-utils/timeutils.hpp
    include/cpp-utils/timedthresholdcounter.hpp
)

set(SOURCES
    logging.cpp
    loggingstdout.cpp
    stringutils.cpp
    base64.cpp
    timeutils.cpp
    timedthresholdcounter.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PRIVATE .                 # "dot" is redundant, because local headers are always available in C/C++.
)

# We intentionally don't make the unit tests dependent on CMAKE_TESTING_ENABLED: so everyone can decide for themselves which unit tests to build
option(ENABLE_CPP_UTILS_TESTING "unit tests for cpp-utils" FALSE)
if(ENABLE_CPP_UTILS_TESTING)
    add_subdirectory(tests)
endif()

