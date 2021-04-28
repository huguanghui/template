#!/bin/sh

TARGET_PATH=/root/amlogic/output/c2_af401_a6432_nand_release/target

# 普通库和进程
#   *-srip --remove-section=.comment --remove-section=.note
# ld-*.so*
#   *-srip --remove-section=.comment --remove-section=.note --strip-debug
# 驱动
#   *-srip --strip-debug
find ${TARGET_PATH} -not \( -name 'iv009_isp' \) -type f \( -perm /111 -o -name '*.so.*' \) \
    -not \( -name 'libpthread*.so*' -o -name 'ld-*.so*' -o -name '*.ko' \) -print0 | xargs -0 echo
