set(TDD_LECTURE_SOURCE_DIRECTORY
    ${TDD_LECTURE_DIR}/src
)

set(TDD_LECTURE_TEST_DIRECTORY
    ${TDD_LECTURE_DIR}/tst
)

set(TDD_LECTURE_MAIN_DIRECTORY
    ${TDD_LECTURE_DIR}/main
)

set(TDD_LECTURE_INCLUDE_DIRECTORIES
    ${TDD_LECTURE_SOURCE_DIRECTORY}
)

set(TDD_LECTURE_TEST_INCLUDE_DIRECTORIES
    ${TDD_LECTURE_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${TDD_LECTURE_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TDD_LECTURE_SOURCE_DIRECTORY_LIST ${TDD_LECTURE_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TDD_LECTURE_SOURCES TDD_LECTURE_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${TDD_LECTURE_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TDD_LECTURE_TEST_DIRECTORY_LIST ${TDD_LECTURE_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TDD_LECTURE_TESTS TDD_LECTURE_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${TDD_LECTURE_MAIN_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(TDD_LECTURE_MAIN_DIRECTORY_LIST ${TDD_LECTURE_MAIN_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(TDD_LECTURE_MAIN_SOURCES TDD_LECTURE_MAIN_DIRECTORY_LIST)

set(TDD_LECTURE_SOURCES_AND_TESTS
    ${TDD_LECTURE_SOURCES}
    ${TDD_LECTURE_TESTS}
)