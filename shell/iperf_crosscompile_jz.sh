#!/usr/bin/env sh

echo "cross compile ..."
ROOT_PATH=$(pwd)
CROSS_COMPILE=mips-linux-gnu-gcc
CROSS_HOST=mips-linux
CROSS_PREFIX=mips-linux-gnu-

# Config
# 4.运行配置
./configure --enable-static-bin --prefix=$(pwd)/_install --host=mips-linux-gnu CC=mips-linux-gnu-gcc CXX=mips-linux-gnu-g++ AR=mips-linux-gnu-ar RANLIB=mips-linux-gnu-ranlib CFLAGS="-muclibc -march=mips32r2" CXXFLAGS="-muclibc -march=mips32r2" LDFLAGS="-muclibc -L/home/yh/Documents/GIT/openssl/openssl-1.1.1q/_install/lib"

# Build
# make
# make install
