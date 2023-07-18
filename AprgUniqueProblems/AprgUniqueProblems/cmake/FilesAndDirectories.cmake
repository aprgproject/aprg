set(APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY
    ${APRG_UNIQUE_PROBLEMS_DIR}/src
)
set(APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY
    ${APRG_UNIQUE_PROBLEMS_DIR}/tst
)

set(APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY
    ${APRG_UNIQUE_PROBLEMS_DIR}/main
)

set(APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES
    ${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY}
)

set(APRG_UNIQUE_PROBLEMS_TEST_INCLUDE_DIRECTORIES
    ${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY_LIST ${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_UNIQUE_PROBLEMS_SOURCES APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY_LIST ${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_UNIQUE_PROBLEMS_TESTS APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY_LIST ${APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_UNIQUE_PROBLEMS_MAIN_SOURCES APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY_LIST)

set(APRG_UNIQUE_PROBLEMS_SOURCES_AND_TESTS
    ${APRG_UNIQUE_PROBLEMS_SOURCES}
    ${APRG_UNIQUE_PROBLEMS_TESTS}
)
