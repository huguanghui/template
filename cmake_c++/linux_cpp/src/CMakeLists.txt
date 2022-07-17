set(PROC_NAME "main")
add_executable(${PROC_NAME} main.cc)
target_compile_features(${PROC_NAME} PUBLIC cxx_std_11)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)

# set(PROC_NAME "test")
# add_library(${PROC_NAME} SHARED test.cc)
# install(TARGETS ${PROC_NAME} RUNTIME DESTINATION lib)
