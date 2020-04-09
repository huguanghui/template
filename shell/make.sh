#!/usr/bin/env sh

#CROSS_COMPILE_PREFIX=arm-himix200-linux
CROSS_COMPILE_PREFIX=
PREFIX_DIR=$(pwd)/../target/

#rm -rf ${PREFIX_DIR}
#mkdir -p ${PREFIX_DIR}

./configure \
    --prefix=${PREFIX_DIR} \
    --enable-ecc \
    --enable-supportedcurves \
    --enable-sniffer \
    --enable-static \
    --enable-tlsv10 \
    --enable-debug \
#    build=${CROSS_COMPILE_PREFIX} \
#    --host=${CROSS_COMPILE_PREFIX} 
#    --enable-debug \
#    CC=${CROSS_COMPILE_PREFIX}-gcc \
# --enable-debug 

make;

make install
