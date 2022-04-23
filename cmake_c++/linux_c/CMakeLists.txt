cmake_minimum_required(VERSION 3.12)

project(demo C)

set(CMAKE_C_STANDARD 99)

# 编译调试开关 set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/_install")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
# "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find_package(HiSiliconSDK REQUIRED)
find_package(Threads REQUIRED)

include_directories(
  src include
  # ${VENDOR_SDK_INCLUDE_DIRS}
)

link_directories(lib)

add_executable(test src/main.c)

target_link_libraries(test Threads::Threads dl m rt stdc++)

install(TARGETS test RUNTIME DESTINATION bin)
