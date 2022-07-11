set(PROC_NAME "test")
add_executable(${PROC_NAME} test.c)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)
