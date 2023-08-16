set(APRG_LOCAL_USER_AUTOMATION_SOURCE_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/src
)

set(APRG_LOCAL_USER_AUTOMATION_TEST_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/tst
)

set(APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/srcWindows
)

set(APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/tstWindows
)

set(APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/srcLinux
)

set(APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY
    ${APRG_LOCAL_USER_AUTOMATION_DIR}/tstLinux
)

PRINT_STATUS("Looking for SRC C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_SOURCES APRG_LOCAL_USER_AUTOMATION_SOURCE_DIRECTORY)

PRINT_STATUS("Looking for TST C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_TESTS APRG_LOCAL_USER_AUTOMATION_TEST_DIRECTORY)

if(WIN32)
    PRINT_STATUS("Looking for Windows SRC C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY}]")
    GET_SUB_DIRECTORY_LIST(APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY_LIST ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY})
    GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCES APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY)

    PRINT_STATUS("Looking for Windows TST C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY}]")
    GET_SUB_DIRECTORY_LIST(APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY_LIST ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY})
    GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_WINDOWS_TESTS APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY)

    set(APRG_LOCAL_USER_AUTOMATION_SOURCES ${APRG_LOCAL_USER_AUTOMATION_SOURCES} ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCES} )
    set(APRG_LOCAL_USER_AUTOMATION_TESTS ${APRG_LOCAL_USER_AUTOMATION_TESTS} ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_TESTS} )
    set(APRG_LOCAL_USER_AUTOMATION_INCLUDE_DIRECTORIES ${APRG_LOCAL_USER_AUTOMATION_SOURCE_DIRECTORY} ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_SOURCE_DIRECTORY} )
    set(APRG_LOCAL_USER_AUTOMATION_TEST_INCLUDE_DIRECTORIES ${APRG_LOCAL_USER_AUTOMATION_TEST_DIRECTORY} ${APRG_LOCAL_USER_AUTOMATION_WINDOWS_TEST_DIRECTORY} )
elseif(UNIX)
    PRINT_STATUS("Looking for Linux SRC C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY}]")
    GET_SUB_DIRECTORY_LIST(APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY_LIST ${APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY})
    GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCES APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY)

    PRINT_STATUS("Looking for Linux TST C/C++ files in: [${APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY}]")
    GET_SUB_DIRECTORY_LIST(APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY_LIST ${APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY})
    GET_SOURCE_FILES_FROM_DIRECTORY(APRG_LOCAL_USER_AUTOMATION_LINUX_TESTS APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY)

    set(APRG_LOCAL_USER_AUTOMATION_SOURCES ${APRG_LOCAL_USER_AUTOMATION_SOURCES} ${APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCES} )
    set(APRG_LOCAL_USER_AUTOMATION_TESTS ${APRG_LOCAL_USER_AUTOMATION_TESTS} ${APRG_LOCAL_USER_AUTOMATION_LINUX_TESTS} )
    set(APRG_LOCAL_USER_AUTOMATION_INCLUDE_DIRECTORIES ${APRG_LOCAL_USER_AUTOMATION_SOURCE_DIRECTORY}  ${APRG_LOCAL_USER_AUTOMATION_LINUX_SOURCE_DIRECTORY} )
    set(APRG_LOCAL_USER_AUTOMATION_TEST_INCLUDE_DIRECTORIES ${APRG_LOCAL_USER_AUTOMATION_TEST_DIRECTORY} ${APRG_LOCAL_USER_AUTOMATION_LINUX_TEST_DIRECTORY} )
endif()

set(APRG_LOCAL_USER_AUTOMATION_SOURCES_AND_TESTS
    ${APRG_LOCAL_USER_AUTOMATION_SOURCES}
    ${APRG_LOCAL_USER_AUTOMATION_TESTS}
)
