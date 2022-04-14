#!/bin/sh

cmake -H. -Bbuild \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_TOOLCHAIN_FILE=tools/cmake/toolchains/mips-linux-gnu-t31.cmake
  # -DPLATFORM_SDK_DIR=<PATH_TO_SDK> \
cmake --build build

