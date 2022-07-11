#!/bin/sh

SOURCE_DIR=$(pwd)

BUILD_TYPE_ARRAY="debug release"
for i in ${BUILD_TYPE_ARRAY}; do
  BUILD_TYPE=${i}
  INSTALL_DIR=output/${BUILD_TYPE}
  BUILD_DIR=build/${BUILD_TYPE}

  cmake -H. -B${BUILD_DIR} \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
    -DCMAKE_TOOLCHAIN_FILE=tools/cmake/toolchains/mips-linux-gnu-t40.cmake
  # -DPLATFORM_SDK_DIR=<PATH_TO_SDK> \
  cmake --build ${BUILD_DIR}
  cmake --install ${BUILD_DIR}
done
