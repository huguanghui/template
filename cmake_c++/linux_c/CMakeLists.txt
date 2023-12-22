cmake_minimum_required(VERSION 3.12)

project(demo VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

enable_language(C CXX ASM)

# 编译调试开关 set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/_install")

message(STATUS "cross compile: ${CMAKE_TOOLCHAIN_FILE}")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
# "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find_package(HiSiliconSDK REQUIRED)
find_package(Threads REQUIRED)

include_directories(
  src inc
  # ${VENDOR_SDK_INCLUDE_DIRS}
)

link_directories(lib)

# aux_source_directory(bm BM_SRC)
add_subdirectory(src)
add_subdirectory(test)
