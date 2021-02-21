[TOC]

# Makefile

## Test

### filter - 过滤函数

source := foo.c bar.c baz.s ugh.h
$(filter %.c %.s, $(source))

### filter-out - 反过滤函数

objects:=main1.o main2.o foo.o bar.o
mains=main1.o main2.o
$(filter-out $(mains), $(objects))
