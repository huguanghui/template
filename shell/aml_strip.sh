#!/bin/sh

TARGET_PATH=/root/amlogic/output/c2_af401_a6432_nand_release/target

find ${TARGET_PATH} -not \( -name 'iv009_isp' \) -type f \( -perm /111 -o -name '*.so.*' \) \
    -not \( -name 'libpthread*.so*' -o -name 'ld-*.so*' -o -name '*.ko' \)
