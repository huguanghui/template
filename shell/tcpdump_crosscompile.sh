#!/usr/bin/env bash

echo "cross compile ..."
ROOT_PATH=`pwd`
CROSS_HOST=arm-himix200-linux
TARGET_PATH=$ROOT_PATH/$CROSS_HOST

PACK_URL=http://www.tcpdump.org/release/libpcap-1.9.1.tar.gz
PACK_PACKAGE=libpcap-1.9.1.tar.gz
PACK_DIR=libpcap-1.9.1

TCPDUMP_URL=https://www.tcpdump.org/release/tcpdump-4.9.3.tar.gz
TCPDUMP_PACKAGE=tcpdump-4.9.3.tar.gz
TCPDUMP_DIR=tcpdump-4.9.3

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

if [ ! -e $PACK_DIR ]; then
    echo "$PACK_DIR not found"
    if [ ! -e $PACK_PACKAGE ]; then
        echo "$PACK_PACKAGE not found"
        remote_get_content "$PACK_URL"
    else
        echo "$PACK_PACKAGE found"
    fi
    tar -xvf $PACK_PACKAGE
else
    echo "$PACK_DIR found"
fi

if [ ! -e $TCPDUMP_DIR ]; then
    echo "$TCPDUMP_DIR not found"
    if [ ! -e $TCPDUMP_PACKAGE ]; then
        echo "$TCPDUMP_PACKAGE not found"
        remote_get_content "$TCPDUMP_URL"
    else
        echo "$TCPDUMP_PACKAGE found"
    fi
    tar -xvf $TCPDUMP_PACKAGE
else
    echo "$TCPDUMP_DIR found"
fi

# Build
cd $PACK_DIR
make clean
./configure --host=$CROSS_HOST --with-pcap=linux

if [[ $? -ne 0 ]]; then
   echo "libpcap ./configure failed" 
   exit 1;
fi

make 

if [[ $? -ne 0 ]]; then
   echo "libpcap make failed" 
   exit 1;
fi

cd $ROOT_PATH

if [ -e $TARGET_PATH ]; then
    rm -rf $TARGET_PATH
fi

mkdir -p $TARGET_PATH

cd $TCPDUMP_DIR
make clean
./configure --host=$CROSS_HOST --prefix=$TARGET_PATH

if [[ $? -ne 0 ]]; then
   echo "tcpdump ./configure failed" 
   exit 1;
fi

make

if [[ $? -ne 0 ]]; then
   echo "tcpdump make failed" 
   exit 1;
fi

make install

cd $ROOT_PATH

