set(PROC_NAME "demo_t1")

add_executable(${PROC_NAME} t1.c)
target_link_libraries(
  ${PROC_NAME}
  Threads::Threads
  dl
  m
  rt)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)

