set(RAGNAROK_ONLINE_SOURCE_DIRECTORY
    ${RAGNAROK_ONLINE_DIR}/src
)
set(RAGNAROK_ONLINE_TEST_DIRECTORY
    ${RAGNAROK_ONLINE_DIR}/tst
)

set(RAGNAROK_ONLINE_MAIN_DIRECTORY
    ${RAGNAROK_ONLINE_DIR}/main
)

set(RAGNAROK_ONLINE_INCLUDE_DIRECTORIES
    ${RAGNAROK_ONLINE_SOURCE_DIRECTORY}
)

set(RAGNAROK_ONLINE_TEST_INCLUDE_DIRECTORIES
    ${RAGNAROK_ONLINE_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${RAGNAROK_ONLINE_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(RAGNAROK_ONLINE_SOURCE_DIRECTORY_LIST ${RAGNAROK_ONLINE_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(RAGNAROK_ONLINE_SOURCES RAGNAROK_ONLINE_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${RAGNAROK_ONLINE_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(RAGNAROK_ONLINE_TEST_DIRECTORY_LIST ${RAGNAROK_ONLINE_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(RAGNAROK_ONLINE_TESTS RAGNAROK_ONLINE_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${RAGNAROK_ONLINE_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(RAGNAROK_ONLINE_MAIN_DIRECTORY_LIST ${RAGNAROK_ONLINE_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(RAGNAROK_ONLINE_MAIN_SOURCES RAGNAROK_ONLINE_MAIN_DIRECTORY_LIST)

set(RAGNAROK_ONLINE_SOURCES_AND_TESTS
    ${RAGNAROK_ONLINE_SOURCES}
    ${RAGNAROK_ONLINE_TESTS}
)
