cmake_minimum_required (VERSION 2.8.12)
project(NVIM_DEPS C)

# check_c_compiler_flag()
# include(CheckCCompilerFlag)

# add custom modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" "${PROJECT_SOURCE_DIR}/../cmake")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# set dir
set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr" CACHE PATH "Dependencies install directory.")
set(DEPS_BIN_DIR "${DEPS_INSTALL_DIR}/bin" CACHE PATH "Dependencies binary install directory.")
set(DEPS_LIB_DIR "${DEPS_INSTALL_DIR}/lib" CACHE PATH "Dependencies library install directory.")
set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build" CACHE PATH "Dependencies build directory")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downlaod" CACHE PATH "Dependencies downlaod directory.")

option(USE_BUNDLED "Use bundled Dependencies." ON)

option(USE_BUNDLED_LIBUV "Use the bundled libuv" ${USE_BUNDLED})
option(USE_BUNDLED_MSGPACK "Use the bundled msgpack" ${USE_BUNDLED})

set(LIBUV_URL https://github.com/libuv/libuv/archive/v1.34.2.tar.gz)
set(LIBUV_SHA256 0d9d38558b45c006c1ea4e8529bae64caf8becda570295ea74e3696362aeb7f2)

set(MSGPACK_URL http://github.com/msgpack/msgpack-c/releases/download/cpp-3.0.0/msgpack-3.0.0.tar.gz)
set(MSGPACK_SHA245 bfbb71b7c02f806393bc3cbc491b40523b89e64f83860c58e3e54af47de176e4)
