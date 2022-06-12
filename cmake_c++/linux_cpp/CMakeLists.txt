cmake_minimum_required(VERSION 3.12)

# if(POLICY CMP0090)
#     cmake_policy(SET CMP0090 NEW)
# endif()

project(demo VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

enable_language(C CXX ASM)

# 编译调试开关
set(CMAKE_VERBOSE_MAKEFILE ON)
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

# aux_source_directory(bm BM_SRC)

set(PROC_NAME "test")
add_executable(${PROC_NAME} src/main.cc)

target_compile_features(${PROC_NAME} PUBLIC cxx_std_11)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)
