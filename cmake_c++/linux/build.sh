#!/bin/sh

SOURCE_DIR=`pwd`
BUILD_TYPE=${BUILD_TYPE:-debug}
INSTALL_DIR=${INSTALL_DIR:-../${BUILD_TYPE}-install}

cmake -H. -Bbuild \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
  # -DCMAKE_TOOLCHAIN_FILE=tools/cmake/toolchains/mips-linux-gnu-t31.cmake
  # -DPLATFORM_SDK_DIR=<PATH_TO_SDK> \
cmake --build build

