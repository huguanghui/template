cmake_minimum_required(VERSION 2.8.12)
project(mini C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_VERBOSE_MAKEFILE OFF)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# find_package(HiSiliconSDK REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    src
    # ${VENDOR_SDK_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    src/t_main.c
)

target_link_libraries(${PROJECT_NAME}
    # ${HILIBS}
    # ${VENDOR_SDK_LIBRARIES}
    Threads::Threads
    dl)

# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
