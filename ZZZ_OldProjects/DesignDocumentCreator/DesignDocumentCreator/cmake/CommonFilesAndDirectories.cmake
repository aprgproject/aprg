set(DD_CREATOR_COMMON_SOURCE_DIRECTORY
    ${DD_CREATOR_DIR}/src/Common/
)

set(DD_CREATOR_COMMON_TEST_DIRECTORY
    ${DD_CREATOR_DIR}/tst/Common/
)

PRINT_STATUS("Looking for sources C/C++ files in: [${DD_CREATOR_COMMON_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(DD_CREATOR_COMMON_SOURCES ${DD_CREATOR_COMMON_SOURCE_DIRECTORY})

PRINT_STATUS("Looking for tests C/C++ files in: [${DD_CREATOR_COMMON_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(DD_CREATOR_COMMON_TESTS ${DD_CREATOR_COMMON_TEST_DIRECTORY})

set(DD_CREATOR_COMMON_SOURCES_AND_TESTS
    ${DD_CREATOR_COMMON_SOURCES}
    ${DD_CREATOR_COMMON_TESTS}
)
