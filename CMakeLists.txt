cmake_minimum_required(VERSION 3.26)
project(ProjectName)

# set(VERSION_MAJOR 8)
# set(VERSION_MINOR 0)
# set(VERSION_PATCH 33)

# 宏定义 还可以用函数实现
# 获取配置值
MACRO(GET_CONFIG_VALUE keyword var)
 IF(NOT ${var})
   FILE (STRINGS ${CMAKE_SOURCE_DIR}/VERSION str REGEX "^[ ]*${keyword}=")
   IF(str)
     STRING(REPLACE "${keyword}=" "" str ${str})
     STRING(REGEX REPLACE  "[ ].*" ""  str "${str}")
     SET(${var} ${str})
   ENDIF()
 ENDIF()
ENDMACRO()
# 获取配置值
GET_CONFIG_VALUE("VERSION_MAJOR" VERSION_MAJOR)
GET_CONFIG_VALUE("VERSION_MINOR" VERSION_MINOR)
GET_CONFIG_VALUE("VERSION_PATCH" VERSION_PATCH)

# 设置多个值，值最终使用分号连接
set(GREETING_WORD ${GREETING_WORD} "hello" "hey")

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
message(STATUS "GREETING_WORD: ${GREETING_WORD}")

configure_file(
    "${PROJECT_SOURCE_DIR}/include/version.h.in"
    "${PROJECT_BINARY_DIR}/include/version.h"
)

# 指定头文件搜索目录 
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}/include")

aux_source_directory("${PROJECT_SOURCE_DIR}/src" SRC_LIST)
message(STATUS "所有源码文件：${SRC_LIST}")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
add_executable(app ${SRC_LIST})


