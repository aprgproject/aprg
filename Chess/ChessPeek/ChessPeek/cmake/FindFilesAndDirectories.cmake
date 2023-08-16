set(CHESS_PEEK_SOURCE_DIRECTORY
    ${CHESS_PEEK_DIR}/src
)

set(CHESS_PEEK_TEST_DIRECTORY
    ${CHESS_PEEK_DIR}/tst
)

set(CHESS_PEEK_MAIN_DIRECTORY
    ${CHESS_PEEK_DIR}/main
)

set(CHESS_PEEK_INCLUDE_DIRECTORIES
    ${CHESS_PEEK_SOURCE_DIRECTORY}
)

set(CHESS_PEEK_TEST_INCLUDE_DIRECTORIES
    ${CHESS_PEEK_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${CHESS_PEEK_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_PEEK_SOURCES CHESS_PEEK_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${CHESS_PEEK_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_PEEK_TESTS CHESS_PEEK_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${CHESS_PEEK_MAIN_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(CHESS_PEEK_MAIN_SOURCES CHESS_PEEK_MAIN_DIRECTORY_LIST)

set(CHESS_PEEK_SOURCES_AND_TESTS
    ${CHESS_PEEK_SOURCES}
    ${CHESS_PEEK_TESTS}
)
