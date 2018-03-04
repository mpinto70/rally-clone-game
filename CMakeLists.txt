cmake_minimum_required (VERSION 2.8.11)
project (rally-clone-game)

# add support for CTest
enable_testing()
include(CTest)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "-Werror \
    -Wall \
    -O2 \
    -finline-functions \
    -std=c++14 \
    -Wno-unused-local-typedefs \
    -D PROJECT_DIR=\"\\\"${CMAKE_SOURCE_DIR}\\\"\" \
    -D RALLY_ROOT=\"\\\"${CMAKE_SOURCE_DIR}\\\"\""
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

include(UnitTest.cmake)
include(CppCheck.cmake)
include(Boost.cmake)

# Recurse subdirectories
add_subdirectory (src)
add_subdirectory (tools)
add_subdirectory (mck)
add_subdirectory (test)
