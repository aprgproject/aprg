set(APRG_GEOMETRY_SOURCE_DIRECTORY
    ${APRG_GEOMETRY_DIR}/src
)

set(APRG_GEOMETRY_TEST_DIRECTORY
    ${APRG_GEOMETRY_DIR}/tst
)

set(APRG_GEOMETRY_INCLUDE_DIRECTORIES
    ${APRG_GEOMETRY_SOURCE_DIRECTORY}
)

set(APRG_GEOMETRY_TEST_INCLUDE_DIRECTORIES
    ${APRG_GEOMETRY_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_GEOMETRY_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GEOMETRY_SOURCES APRG_GEOMETRY_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_GEOMETRY_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_GEOMETRY_TESTS APRG_GEOMETRY_TEST_DIRECTORY_LIST)

set(APRG_GEOMETRY_SOURCES_AND_TESTS
    ${APRG_GEOMETRY_SOURCES}
    ${APRG_GEOMETRY_TESTS}
)
