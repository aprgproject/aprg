set(APRG_CODE_REVIEW_SOURCE_DIRECTORY
    ${APRG_CODE_REVIEW_DIR}/src
)

set(APRG_CODE_REVIEW_TEST_DIRECTORY
    ${APRG_CODE_REVIEW_DIR}/tst
)

set(APRG_CODE_REVIEW_MAIN_DIRECTORY
    ${APRG_CODE_REVIEW_DIR}/main
)

set(APRG_CODE_REVIEW_INCLUDE_DIRECTORIES
    ${APRG_CODE_REVIEW_SOURCE_DIRECTORY}
)

set(APRG_CODE_REVIEW_TEST_INCLUDE_DIRECTORIES
    ${APRG_CODE_REVIEW_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for sources C/C++ files in: [${APRG_CODE_REVIEW_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_CODE_REVIEW_SOURCES ${APRG_CODE_REVIEW_SOURCE_DIRECTORY})

PRINT_STATUS("Looking for tests C/C++ files in: [${APRG_CODE_REVIEW_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_CODE_REVIEW_TESTS ${APRG_CODE_REVIEW_TEST_DIRECTORY})

PRINT_STATUS("Looking for main C/C++ files in: [${APRG_CODE_REVIEW_MAIN_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_CODE_REVIEW_MAIN_SOURCES ${APRG_CODE_REVIEW_MAIN_DIRECTORY})

set(APRG_CODE_REVIEW_SOURCES_AND_TESTS
    ${APRG_CODE_REVIEW_SOURCES}
    ${APRG_CODE_REVIEW_TESTS}
)
