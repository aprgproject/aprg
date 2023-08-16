set(APRG_BITMAP_SOURCE_DIRECTORY
    ${APRG_BITMAP_DIR}/src
)

set(APRG_BITMAP_TEST_DIRECTORY
    ${APRG_BITMAP_DIR}/tst
)

set(APRG_BITMAP_INCLUDE_DIRECTORIES
    ${APRG_BITMAP_SOURCE_DIRECTORY}
)

set(APRG_BITMAP_TEST_INCLUDE_DIRECTORIES
    ${APRG_BITMAP_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC C/C++ files in: [${APRG_BITMAP_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_BITMAP_SOURCES APRG_BITMAP_SOURCE_DIRECTORY)

PRINT_STATUS("Looking for TST C/C++ files in: [${APRG_BITMAP_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_BITMAP_TESTS APRG_BITMAP_TEST_DIRECTORY)

set(APRG_BITMAP_SOURCES_AND_TESTS
    ${APRG_BITMAP_SOURCES}
    ${APRG_BITMAP_TESTS}
)
