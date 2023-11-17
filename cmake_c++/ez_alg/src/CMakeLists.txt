set(PROC_NAME "alg")

add_library(${PROC_NAME} STATIC "")
aux_source_directory(. MOD_SRC)
list(APPEND ALG_SRC ${MOD_SRC})
target_sources(${PROC_NAME} PRIVATE ${ALG_SRC})


install(TARGETS ${PROC_NAME} RUNTIME DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/inc/ DESTINATION include)
