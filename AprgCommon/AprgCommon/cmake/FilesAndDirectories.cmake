include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)

set(APRG_COMMON_SOURCE_DIRECTORY
    ${APRG_COMMON_DIR}/src
)

set(APRG_COMMON_TEST_DIRECTORY
    ${APRG_COMMON_DIR}/tst
)

set(APRG_COMMON_WINDOWS_SOURCE_DIRECTORY
    ${APRG_COMMON_DIR}/srcWindows
)

set(APRG_COMMON_WINDOWS_TEST_DIRECTORY
    ${APRG_COMMON_DIR}/tstWindows
)

set(APRG_COMMON_INCLUDE_DIRECTORIES
    ${APRG_COMMON_SOURCE_DIRECTORY}
)

set(APRG_COMMON_TEST_INCLUDE_DIRECTORIES
    ${APRG_COMMON_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_COMMON_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_COMMON_SOURCE_DIRECTORY_LIST ${APRG_COMMON_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_COMMON_SOURCES APRG_COMMON_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_COMMON_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_COMMON_TEST_DIRECTORY_LIST ${APRG_COMMON_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_COMMON_TESTS APRG_COMMON_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for Windows SRC directories in: [${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_COMMON_WINDOWS_SOURCE_DIRECTORY_LIST ${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_COMMON_WINDOWS_SOURCES APRG_COMMON_WINDOWS_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for Windows TST directories in: [${APRG_COMMON_WINDOWS_TEST_DIRECTORY}]")
GET_SUB_DIRECTORY_LIST(APRG_COMMON_WINDOWS_TEST_DIRECTORY_LIST ${APRG_COMMON_WINDOWS_TEST_DIRECTORY})
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_COMMON_WINDOWS_TESTS APRG_COMMON_WINDOWS_TEST_DIRECTORY_LIST)

if(WIN32)
    set(APRG_COMMON_SOURCES
        ${APRG_COMMON_SOURCES}
        ${APRG_COMMON_WINDOWS_SOURCES}
        )
    set(APRG_COMMON_TESTS
        ${APRG_COMMON_TESTS}
        ${APRG_COMMON_WINDOWS_TESTS}
        )
    set(APRG_COMMON_INCLUDE_DIRECTORIES
        ${APRG_COMMON_INCLUDE_DIRECTORIES}
        ${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY}
        )
    set(APRG_COMMON_TEST_INCLUDE_DIRECTORIES
        ${APRG_COMMON_TEST_INCLUDE_DIRECTORIES}
        ${APRG_COMMON_WINDOWS_TEST_DIRECTORY}
        )
endif()

set(APRG_COMMON_SOURCES_AND_TESTS
    ${APRG_COMMON_SOURCES}
    ${APRG_COMMON_TESTS}
)