set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compiler.
set(CMAKE_C_COMPILER
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
    CACHE FILEPATH "C compiler")
set(CMAKE_CXX_COMPILER
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
    CACHE FILEPATH "C++ compiler")
set(CMAKE_ASM_COMPILER
    /opt/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc
    CACHE FILEPATH "ASM compiler")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -funwind-tables -rdynamic -mcpu=cortex-a7 -mfpu=neon-vfpv4 -ffunction-sections -fdata-sections -fstack-protector -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funwind-tables -rdynamic -mcpu=cortex-a7 -mfpu=neon-vfpv4 -ffunction-sections -fdata-sections -fstack-protector -Wall")

# Search libraries only under *target* paths.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
