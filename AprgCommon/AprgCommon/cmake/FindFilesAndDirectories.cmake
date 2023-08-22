set(APRG_COMMON_SOURCE_DIRECTORY ${APRG_COMMON_DIR}/src)

set(APRG_COMMON_TEST_UTILITIES_DIRECTORY ${APRG_COMMON_DIR}/tstUtilities)

set(APRG_COMMON_TEST_DIRECTORY ${APRG_COMMON_DIR}/tst)

set(APRG_COMMON_WINDOWS_SOURCE_DIRECTORY ${APRG_COMMON_DIR}/srcWindows)

set(APRG_COMMON_WINDOWS_TEST_DIRECTORY ${APRG_COMMON_DIR}/tstWindows)

set(APRG_COMMON_LINUX_SOURCE_DIRECTORY ${APRG_COMMON_DIR}/srcLinux)

set(APRG_COMMON_LINUX_TEST_DIRECTORY ${APRG_COMMON_DIR}/tstLinux)

print_status("Looking for sources C/C++ files in: [${APRG_COMMON_SOURCE_DIRECTORY}]")
get_source_files_from_directory(APRG_COMMON_SOURCES ${APRG_COMMON_SOURCE_DIRECTORY})

print_status("Looking for common tests utilities C/C++ files in: [${APRG_COMMON_TEST_UTILITIES_DIRECTORY}]")
get_source_files_from_directory(APRG_COMMON_SOURCES ${APRG_COMMON_TEST_UTILITIES_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${APRG_COMMON_TEST_DIRECTORY}]")
get_source_files_from_directory(APRG_COMMON_TESTS ${APRG_COMMON_TEST_DIRECTORY})

if(WIN32)
    print_status("Looking for windows sources C/C++ files in: [${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY}]")
    get_source_files_from_directory(APRG_COMMON_WINDOWS_SOURCES ${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY})

    print_status("Looking for windows tests C/C++ files in: [${APRG_COMMON_WINDOWS_TEST_DIRECTORY}]")
    get_source_files_from_directory(APRG_COMMON_WINDOWS_TESTS ${APRG_COMMON_WINDOWS_TEST_DIRECTORY})

    set(APRG_COMMON_SOURCES ${APRG_COMMON_SOURCES} ${APRG_COMMON_WINDOWS_SOURCES})
    set(APRG_COMMON_TESTS ${APRG_COMMON_TESTS} ${APRG_COMMON_WINDOWS_TESTS})
    set(APRG_COMMON_INCLUDE_DIRECTORIES ${APRG_COMMON_SOURCE_DIRECTORY} ${APRG_COMMON_WINDOWS_SOURCE_DIRECTORY}
                                        ${APRG_COMMON_TEST_UTILITIES_DIRECTORY})
    set(APRG_COMMON_TEST_INCLUDE_DIRECTORIES ${APRG_COMMON_TEST_DIRECTORY} ${APRG_COMMON_WINDOWS_TEST_DIRECTORY})
elseif(UNIX)
    print_status("Looking for linux sources C/C++ files in: [${APRG_COMMON_LINUX_SOURCE_DIRECTORY}]")
    get_source_files_from_directory(APRG_COMMON_LINUX_SOURCES ${APRG_COMMON_LINUX_SOURCE_DIRECTORY})

    print_status("Looking for linux tests C/C++ files in: [${APRG_COMMON_LINUX_TEST_DIRECTORY}]")
    get_source_files_from_directory(APRG_COMMON_LINUX_TESTS ${APRG_COMMON_LINUX_TEST_DIRECTORY})

    set(APRG_COMMON_SOURCES ${APRG_COMMON_SOURCES} ${APRG_COMMON_LINUX_SOURCES})
    set(APRG_COMMON_TESTS ${APRG_COMMON_TESTS} ${APRG_COMMON_LINUX_TESTS})
    set(APRG_COMMON_INCLUDE_DIRECTORIES ${APRG_COMMON_SOURCE_DIRECTORY} ${APRG_COMMON_LINUX_SOURCE_DIRECTORY}
                                        ${APRG_COMMON_TEST_UTILITIES_DIRECTORY})
    set(APRG_COMMON_TEST_INCLUDE_DIRECTORIES ${APRG_COMMON_TEST_DIRECTORY} ${APRG_COMMON_LINUX_TEST_DIRECTORY})
endif()

set(APRG_COMMON_SOURCES_AND_TESTS ${APRG_COMMON_SOURCES} ${APRG_COMMON_TESTS})
