#!/bin/sh

SOURCE_DIR=$(pwd)

export MAKEFLAGS='--no-print-directory'

# BUILD_TYPE_ARRAY="debug release"
BUILD_TYPE_ARRAY="debug"
for i in ${BUILD_TYPE_ARRAY}; do
  BUILD_TYPE=${i}
  INSTALL_DIR=output/${BUILD_TYPE}
  #INSTALL_DIR=/home/hgh/workspace/nfs/jz_webrtc
  BUILD_DIR=build/${BUILD_TYPE}

  cmake -H. -B${BUILD_DIR} \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
    # -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/arm-linux-gnu-sv823c_glibc_gcc750.cmake
  cmake --build ${BUILD_DIR} -j8
  cmake --install ${BUILD_DIR}
done
