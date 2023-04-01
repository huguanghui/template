#!/bin/sh

../gdb-7.11/configure --host=mips-linux-gnu --prefix=$(pwd)/_install CFLAGS="-g -std=gnu99 -lpthread -muclibc -march=mips32r2" CXXFLAGS="-std=c++11 -muclibc -march=mips32r2" LD="/opt/gcc_720/mips-gcc720-glibc229-r5.1.4/bin/mips-linux-gnu-ld" LDFLAGS="-muclibc" CC="/opt/gcc_720/mips-gcc720-glibc229-r5.1.4/bin/mips-linux-gnu-gcc" CXX="/opt/gcc_720/mips-gcc720-glibc229-r5.1.4/bin/mips-linux-gnu-g++" AR="/opt/gcc_720/mips-gcc720-glibc229-r5.1.4/bin/mips-linux-gnu-ar" --disable-werror

