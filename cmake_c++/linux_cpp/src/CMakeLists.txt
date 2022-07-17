set(PROC_NAME "main")
add_executable(${PROC_NAME} main.cc)
# set_target_properties(cls_queue PROPERTIES
#   VERSION "1.0.0"
#   SOVERSION "1"
#   INSTALL_RPATH ""
#   CXX_VISIBILITY_PRESET hidden)
# install(TARGETS cls_queue DESTINATION ${cls_dir})
target_compile_features(${PROC_NAME} PUBLIC cxx_std_11)
target_link_libraries(${PROC_NAME} Threads::Threads dl m rt stdc++)

install(TARGETS ${PROC_NAME} RUNTIME DESTINATION bin)

# set(PROC_NAME "test")
# add_library(${PROC_NAME} SHARED test.cc)
# set_target_properties(cls_queue PROPERTIES
#   VERSION "1.0.0"
#   SOVERSION "1"
#   INSTALL_RPATH ""
#   CXX_VISIBILITY_PRESET hidden)
# install(TARGETS cls_queue DESTINATION ${cls_dir})
# install(TARGETS ${PROC_NAME} RUNTIME DESTINATION lib)
