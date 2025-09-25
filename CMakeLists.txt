cmake_minimum_required(VERSION 3.10)
project(nowrd)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_DEBUG "-g")


# Collect all source files
file(GLOB_RECURSE SOURCES
    source/*.cc
)

find_package(raylib REQUIRED)

add_executable(nowrd ${SOURCES})
target_link_libraries(nowrd PRIVATE raylib)
