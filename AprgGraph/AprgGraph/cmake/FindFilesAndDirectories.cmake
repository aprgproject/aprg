set(APRG_GRAPH_SOURCE_DIRECTORY
    ${APRG_GRAPH_DIR}/src
)

set(APRG_GRAPH_TEST_DIRECTORY
    ${APRG_GRAPH_DIR}/tst
)

set(APRG_GRAPH_INCLUDE_DIRECTORIES
    ${APRG_GRAPH_SOURCE_DIRECTORY}
)

set(APRG_GRAPH_TEST_INCLUDE_DIRECTORIES
    ${APRG_GRAPH_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC C/C++ files in: [${APRG_GRAPH_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_GRAPH_SOURCES APRG_GRAPH_SOURCE_DIRECTORY)

PRINT_STATUS("Looking for TST C/C++ files in: [${APRG_GRAPH_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_GRAPH_TESTS APRG_GRAPH_TEST_DIRECTORY)

set(APRG_GRAPH_SOURCES_AND_TESTS
    ${APRG_GRAPH_SOURCES}
    ${APRG_GRAPH_TESTS}
)
