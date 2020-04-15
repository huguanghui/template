#!/bin/bash

echo "cross compile ..."
ROOT_PATH=`pwd`
PREFIX=$ROOT_PATH/Build_Lib
#CROSS_COMPILE_HOST=arm-himix200-linux
#STRIP=${CROSS_COMPILE_HOST}-strip
#CC=${CROSS_COMPILE_HOST}-gcc

ZLIB_URL=http://prdownloads.sourceforge.net/libpng/zlib-1.2.11.tar.gz
ZLIB_PACKAGE=zlib-1.2.11.tar.gz
ZLIB_DIR=zlib-1.2.11
CURL_URL=https://curl.haxx.se/download/curl-7.49.1.tar.gz
CURL_PACKAGE=curl-7.49.1.tar.gz
CURL_DIR=curl-7.49.1

WOLFSSL_URL=https://sourceforge.net/projects/wolfssl/files/v3.15.3-stable/wolfSSL%20release%20version%203.15.3.tar.gz
WOLFSSL_DIR=target

OPENSSL_URL=https://www.openssl.org/source/openssl-1.1.1d.tar.gz
OPENSSL_PACKAGE=openssl-1.1.1d.tar.gz
OPENSSL_DIR=openssl-1.1.1d

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

#if [ ! -e $ZLIB_DIR ]; then
#    echo "$ZLIB_DIR not found"
#    if [ ! -e $ZLIB_PACKAGE ]; then
#        echo "$ZLIB_PACKAGE not found"
#        remote_get_content "$ZLIB_URL"
#    else
#        echo "$ZLIB_PACKAGE found"
#    fi
#    tar -xvf $ZLIB_PACKAGE
#else
#    echo "$ZLIB_DIR found"
#fi
#
#
#if [ ! -e $OPENSSL_DIR ]; then
#    echo "$OPENSSL_DIR not found"
#    if [ ! -e $OPENSSL_PACKAGE ]; then
#        echo "$OPENSSL_PACKAGE not found"
#        remote_get_content "$OPENSSL_URL"
#    else
#        echo "$OPENSSL_PACKAGE found"
#    fi
#    tar -xvf $OPENSSL_PACKAGE
#else
#    echo "$OPENSSL_DIR found"
#fi

# Config

# 4.运行配置
cd $ROOT_PATH/$CURL_DIR;
if [ -d $PREFIX ]; then
    rm -rf $PREFIX
fi
mkdir -p $PREFIX
#make clean
#make distclean

#./configure \
#    --prefix=$PREFIX \
#    --enable-static \
#    --enable-shared=no \
#    --host=$CROSS_COMPILE_HOST \
#    --target=$CROSS_COMPILE_HOST \
#    --with-cyassl=$ROOT_PATH/$WOLFSSL_DIR \
#    --enable-nonblocking \
#    --disable-tftp \
#    --disable-telnet \
#    --disable-manual \
#    --enable-file \
#    --without-libssh2 \
#    --without-random \
#    --without-nss \
#    --without-ca-bundle \
#    --without-libidn \
#    --disable-ipv6 \
#    --disable-largefile \
#    --enable-debug \
#    --enable-curldebug

./configure \
    --prefix=$PREFIX \
    --enable-static \
    --enable-shared=no \
    --disable-largefile \
    --without-ssl \
    --with-cyassl=$ROOT_PATH/$WOLFSSL_DIR \
    --without-zlib \
    --without-librtsp \
    --without-librtmp \
    --without-nghttp2 \
    --without-ldap \
    --enable-nonblocking \
    --disable-tftp \
    --disable-telnet \
    --disable-manual \
    --enable-file \
    --without-libssh2 \
    --without-random \
    --without-nss \
    --without-ca-bundle \
    --without-libidn \
    --disable-ipv6 \
    --disable-largefile \
    --enable-debug 

# 5.补充宏

# Build
#make;
#make install
