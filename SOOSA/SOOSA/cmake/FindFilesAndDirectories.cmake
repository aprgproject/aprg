set(SOOSA_SOURCE_DIRECTORY ${SOOSA_DIR}/src)

set(SOOSA_TEST_DIRECTORY ${SOOSA_DIR}/tst)

set(SOOSA_MAIN_DIRECTORY ${SOOSA_DIR}/main)

set(SOOSA_INCLUDE_DIRECTORIES ${SOOSA_SOURCE_DIRECTORY})

set(SOOSA_TEST_INCLUDE_DIRECTORIES ${SOOSA_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${SOOSA_SOURCE_DIRECTORY}]")
get_source_files_from_directory(SOOSA_SOURCES ${SOOSA_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${SOOSA_TEST_DIRECTORY}]")
get_source_files_from_directory(SOOSA_TESTS ${SOOSA_TEST_DIRECTORY})

print_status("Looking for main C/C++ files in: [${SOOSA_MAIN_DIRECTORY}]")
get_source_files_from_directory(SOOSA_MAIN_SOURCES ${SOOSA_MAIN_DIRECTORY})

set(SOOSA_SOURCES_AND_TESTS ${SOOSA_SOURCES} ${SOOSA_TESTS})
