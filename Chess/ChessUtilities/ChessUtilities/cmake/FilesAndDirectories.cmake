set(CHESS_UTILITIES_SOURCE_DIRECTORY
    ${CHESS_UTILITIES_DIR}/src
)

set(CHESS_UTILITIES_TEST_DIRECTORY
    ${CHESS_UTILITIES_DIR}/tst
)

set(CHESS_UTILITIES_MAIN_DIRECTORY
    ${CHESS_UTILITIES_DIR}/main
)

set(CHESS_UTILITIES_INCLUDE_DIRECTORIES
    ${CHESS_UTILITIES_SOURCE_DIRECTORY}
)

set(CHESS_UTILITIES_TEST_INCLUDE_DIRECTORIES
    ${CHESS_UTILITIES_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${CHESS_UTILITIES_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CHESS_UTILITIES_SOURCE_DIRECTORY_LIST ${CHESS_UTILITIES_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_UTILITIES_SOURCES CHESS_UTILITIES_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${CHESS_UTILITIES_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CHESS_UTILITIES_TEST_DIRECTORY_LIST ${CHESS_UTILITIES_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_UTILITIES_TESTS CHESS_UTILITIES_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${CHESS_UTILITIES_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(CHESS_UTILITIES_MAIN_DIRECTORY_LIST ${CHESS_UTILITIES_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_UTILITIES_MAIN_SOURCES CHESS_UTILITIES_MAIN_DIRECTORY_LIST)

set(CHESS_UTILITIES_SOURCES_AND_TESTS
    ${CHESS_UTILITIES_SOURCES}
    ${CHESS_UTILITIES_TESTS}
)
