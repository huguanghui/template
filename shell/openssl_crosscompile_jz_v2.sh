#!/usr/bin/env sh

echo "cross compile ..."
ROOT_PATH=$(pwd)
CROSS_COMPILE=mips-linux-gnu-gcc
CROSS_HOST=mips-linux-gnu
CROSS_PREFIX=mips-linux-gnu-

OPENSSL_URL=https://www.openssl.org/source/old/1.1.1/openssl-1.1.1q.tar.gz
OPENSSL_PACKAGE=openssl-1.1.1q.tar.gz
OPENSSL_DIR=openssl-1.1.1q

remote_get_content() {
  wget "$1"
  #    if curl --version >/dev/null 2>&1
  #    then
  #        curl -fSL "$1"
  #    elif wget --version >/dev/null 2>&1
  #    then
  #        wget "$1" -0 -
  #    fi
}

# "Prepare Package"

if [ ! -e $OPENSSL_DIR ]; then
  echo "$OPENSSL_DIR not found"
  if [ ! -e $OPENSSL_PACKAGE ]; then
    echo "$OPENSSL_PACKAGE not found"
    remote_get_content "$OPENSSL_URL"
  else
    echo "$OPENSSL_PACKAGE found"
  fi
  tar -xvf $OPENSSL_PACKAGE
else
  echo "$OPENSSL_DIR found"
fi

# Config
# 4.运行配置
cd $ROOT_PATH/$OPENSSL_DIR
if [ -d $ROOT_PATH/$OPENSSL_DIR/.tmp ]; then
  rm -rf $ROOT_PATH/$OPENSSL_DIR/.tmp
fi
mkdir -p $ROOT_PATH/$OPENSSL_DIR/.tmp
./Configure no-asm no-shared no-async no-threads linux-mips32 --cross-compile-prefix=mips-linux-gnu- CFLAGS="-muclibc -march=mips32r2" CXXFLAGS="-muclibc -march=mips32r2" LDFLAGS="-muclibc" --prefix=$(pwd)/_install
sed -i "s/ -m64//g" ./Makefile

# Build
make
make install
