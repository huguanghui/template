set(PROC_NAME "main")
add_executable(${PROC_NAME} main.c)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)

# set(PROC_NAME "test")
# add_library(${PROC_NAME} SHARED test.c)
# install(TARGETS ${PROC_NAME} RUNTIME DESTINATION lib)
