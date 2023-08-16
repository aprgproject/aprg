set(APRG_BOOLEAN_ALGEBRA_SOURCE_DIRECTORY
    ${APRG_BOOLEAN_ALGEBRA_DIR}/src
)

set(APRG_BOOLEAN_ALGEBRA_TEST_DIRECTORY
    ${APRG_BOOLEAN_ALGEBRA_DIR}/tst
)

set(APRG_BOOLEAN_ALGEBRA_MAIN_DIRECTORY
    ${APRG_BOOLEAN_ALGEBRA_DIR}/main
)

set(APRG_BOOLEAN_ALGEBRA_INCLUDE_DIRECTORIES
    ${APRG_BOOLEAN_ALGEBRA_SOURCE_DIRECTORY}
)

set(APRG_BOOLEAN_ALGEBRA_TEST_INCLUDE_DIRECTORIES
    ${APRG_BOOLEAN_ALGEBRA_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_BOOLEAN_ALGEBRA_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_BOOLEAN_ALGEBRA_SOURCES APRG_BOOLEAN_ALGEBRA_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_BOOLEAN_ALGEBRA_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_BOOLEAN_ALGEBRA_TESTS APRG_BOOLEAN_ALGEBRA_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${APRG_BOOLEAN_ALGEBRA_MAIN_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_BOOLEAN_ALGEBRA_MAIN_SOURCES APRG_BOOLEAN_ALGEBRA_MAIN_DIRECTORY_LIST)

set(APRG_BOOLEAN_ALGEBRA_SOURCES_AND_TESTS
    ${APRG_BOOLEAN_ALGEBRA_SOURCES}
    ${APRG_BOOLEAN_ALGEBRA_TESTS}
)
