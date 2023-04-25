cmake_minimum_required(VERSION 3.26)
project(ProjectName)

set(VERSION_MAJOR 8)
set(VERSION_MINOR 0)
set(VERSION_PATCH 33)

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

configure_file(
    "${PROJECT_SOURCE_DIR}/include/version.h.in"
    "${PROJECT_BINARY_DIR}/include/version.h"
)


# include_directories("${PROJECT_SOURCE_DIR}/include")
# add_subdirectory("${PROJECT_SOURCE_DIR}/src")

# 指定头文件搜索目录
include_directories("${PROJECT_BINARY_DIR}/include")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
add_executable(app "${PROJECT_SOURCE_DIR}/src/main.cc")


