set(APRG_GRAPH_SOURCE_DIRECTORY ${APRG_GRAPH_DIR}/src)

set(APRG_GRAPH_TEST_DIRECTORY ${APRG_GRAPH_DIR}/tst)

set(APRG_GRAPH_INCLUDE_DIRECTORIES ${APRG_GRAPH_SOURCE_DIRECTORY})

set(APRG_GRAPH_TEST_INCLUDE_DIRECTORIES ${APRG_GRAPH_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${APRG_GRAPH_SOURCE_DIRECTORY}]")
get_source_files_from_directory(APRG_GRAPH_SOURCES ${APRG_GRAPH_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${APRG_GRAPH_TEST_DIRECTORY}]")
get_source_files_from_directory(APRG_GRAPH_TESTS ${APRG_GRAPH_TEST_DIRECTORY})

set(APRG_GRAPH_SOURCES_AND_TESTS ${APRG_GRAPH_SOURCES} ${APRG_GRAPH_TESTS})
