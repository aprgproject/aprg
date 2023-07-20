set(BTS_LOG_ANALYZER_SOURCE_DIRECTORY
    ${BTS_LOG_ANALYZER_DIR}/src
)

set(BTS_LOG_ANALYZER_TEST_DIRECTORY
    ${BTS_LOG_ANALYZER_DIR}/tst
)

set(BTS_LOG_ANALYZER_INCLUDE_DIRECTORIES
    ${BTS_LOG_ANALYZER_SOURCE_DIRECTORY}
)

set(BTS_LOG_ANALYZER_TEST_INCLUDE_DIRECTORIES
    ${BTS_LOG_ANALYZER_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${BTS_LOG_ANALYZER_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_LOG_ANALYZER_SOURCE_DIRECTORY_LIST ${BTS_LOG_ANALYZER_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_LOG_ANALYZER_SOURCES BTS_LOG_ANALYZER_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${BTS_LOG_ANALYZER_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(BTS_LOG_ANALYZER_TEST_DIRECTORY_LIST ${BTS_LOG_ANALYZER_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(BTS_LOG_ANALYZER_TESTS BTS_LOG_ANALYZER_TEST_DIRECTORY_LIST)

set(BTS_LOG_ANALYZER_SOURCES_AND_TESTS
    ${BTS_LOG_ANALYZER_SOURCES}
    ${BTS_LOG_ANALYZER_TESTS}
)
