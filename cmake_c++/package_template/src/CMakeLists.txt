set(PROC_NAME "main")
add_executable(${PROC_NAME} main.c)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)
