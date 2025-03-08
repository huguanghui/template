cmake_minimum_required(VERSION 3.12)

# if(POLICY CMP0090) cmake_policy(SET CMP0090 NEW) endif()

project(demo VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)

enable_language(C CXX ASM)

# 编译调试开关 set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_MESSAGE NEVER)
# set(CMAKE_BUILD_TYPE "Debug") set(CMAKE_INSTALL_PREFIX
# "${CMAKE_SOURCE_DIR}/_install")

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold "${Esc}[1m")
  set(Red "${Esc}[31m")
  set(Green "${Esc}[32m")
  set(Yellow "${Esc}[33m")
  set(Blue "${Esc}[34m")
  set(Magenta "${Esc}[35m")
  set(Cyan "${Esc}[36m")
  set(White "${Esc}[37m")
  set(BoldRed "${Esc}[1;31m")
  set(BoldGreen "${Esc}[1;32m")
  set(BoldYellow "${Esc}[1;33m")
  set(BoldBlue "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan "${Esc}[1;36m")
  set(BoldWhite "${Esc}[1;37m")
endif()

message("${BoldMagenta}slient mode${ColourReset}")
set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

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
