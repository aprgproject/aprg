set(DD_CREATOR_COMMON_SOURCE_DIRECTORY
    ${DD_CREATOR_DIR}/src/Common/
)

set(DD_CREATOR_COMMON_TEST_DIRECTORY
    ${DD_CREATOR_DIR}/tst/Common/
)

PRINT_STATUS("Looking for SRC directories in: [${DD_CREATOR_COMMON_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(DD_CREATOR_COMMON_SOURCES DD_CREATOR_COMMON_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${DD_CREATOR_COMMON_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(DD_CREATOR_COMMON_TESTS DD_CREATOR_COMMON_TEST_DIRECTORY_LIST)

set(DD_CREATOR_COMMON_SOURCES_AND_TESTS
    ${DD_CREATOR_COMMON_SOURCES}
    ${DD_CREATOR_COMMON_TESTS}
)
