#!/usr/bin/env bash

echo "cross compile ..." ROOT_PATH=`pwd`
CROSS_HOST=arm-himix200-linux
TARGET_PATH=$ROOT_PATH/$CROSS_HOST

GDB_URL=http://ftp.gnu.org/gnu/gdb/gdb-9.1.tar.gz
GDB_PACKAGE=`echo $GDB_URL | sed -e 's/^.*\/\(.*\)/\1/'`
GDB_DIR=`echo $GDB_PACKAGE | sed -e 's/^\(.*\)\..*\..*/\1/'`

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

pre_done() {
    echo $1 $2 $3
    if [ ! -e $3 ]; then
        echo "$3 not found"
        if [ ! -e $2 ]; then
            echo "$2 not found"
            remote_get_content "$1"
       else
            echo "$2 found"
        fi
        tar -xvf $2
    else
        echo "$3 found"
    fi
}

pre_done $GDB_URL $GDB_PACKAGE $GDB_DIR

# Build
#cd $PACK_DIR
#make clean
#./configure --host=$CROSS_HOST --with-pcap=linux
#
#if [[ $? -ne 0 ]]; then
#   echo "libpcap ./configure failed" 
#   exit 1;
#fi
#
#make 
#
#if [[ $? -ne 0 ]]; then
#   echo "libpcap make failed" 
#   exit 1;
#fi
#
#cd $ROOT_PATH
#
#if [ -e $TARGET_PATH ]; then
#    rm -rf $TARGET_PATH
#fi
#
#mkdir -p $TARGET_PATH
#
#cd $TCPDUMP_DIR
#make clean
#./configure --host=$CROSS_HOST --prefix=$TARGET_PATH
#
#if [[ $? -ne 0 ]]; then
#   echo "tcpdump ./configure failed" 
#   exit 1;
#fi
#
#make
#
#if [[ $? -ne 0 ]]; then
#   echo "tcpdump make failed" 
#   exit 1;
#fi
#
#make install
#
#cd $ROOT_PATH
#
