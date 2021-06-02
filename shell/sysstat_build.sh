#!/bin/sh

ROOT_DIR=$(pwd)
CC=arm-linux-gnueabihf-gcc ./configure --host=arm --cache-file=${ROOT_DIR}/.tmp/cache --prefix=${ROOT_DIR}/.tmp/out --exec-prefix=${ROOT_DIR}/.tmp/exe
