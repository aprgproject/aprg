set(WCDMA_TOOLS_BACKEND_SOURCE_DIRECTORY
    ${WCDMA_TOOLS_BACKEND_DIR}/src
)

set(WCDMA_TOOLS_BACKEND_TEST_DIRECTORY
    ${WCDMA_TOOLS_BACKEND_DIR}/tst
)

set(WCDMA_TOOLS_BACKEND_INCLUDE_DIRECTORIES
    ${WCDMA_TOOLS_BACKEND_SOURCE_DIRECTORY}
)

set(WCDMA_TOOLS_BACKEND_TEST_INCLUDE_DIRECTORIES
    ${WCDMA_TOOLS_BACKEND_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for sources C/C++ files in: [${WCDMA_TOOLS_BACKEND_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(WCDMA_TOOLS_BACKEND_SOURCES ${WCDMA_TOOLS_BACKEND_SOURCE_DIRECTORY})

PRINT_STATUS("Looking for tests C/C++ files in: [${WCDMA_TOOLS_BACKEND_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(WCDMA_TOOLS_BACKEND_TESTS ${WCDMA_TOOLS_BACKEND_TEST_DIRECTORY})

set(WCDMA_TOOLS_BACKEND_SOURCES_AND_TESTS
    ${WCDMA_TOOLS_BACKEND_SOURCES}
    ${WCDMA_TOOLS_BACKEND_TESTS}
)
