cmake_minimum_required(VERSION 3.12)

project(ez_alg VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

enable_language(C CXX ASM)

# 编译调试开关 set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

find_package(Threads REQUIRED)

if(CHIP STREQUAL "sv822")
  set(EZ_NDK_DIR ${CMAKE_SOURCE_DIR}/depend/sv822_ndk)
  add_definitions(-DNDK_SV822)
else()
  # sv823
  set(EZ_NDK_DIR ${CMAKE_SOURCE_DIR}/depend/sv823_ndk)
  add_definitions(-DNDK_SV823)
endif()

message(STATUS "ndk_dir: ${EZ_NDK_DIR}")
message(STATUS "cross compile: ${CMAKE_TOOLCHAIN_FILE}")

include_directories(inc ${EZ_NDK_DIR}/include)
link_directories(${EZ_NDK_DIR}/libs)
set(EZ_NDK_LINKS "nn" "openvx-nn" "openvx")

add_subdirectory(src)
add_subdirectory(demo)
