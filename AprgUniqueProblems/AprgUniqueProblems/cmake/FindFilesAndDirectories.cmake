set(APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY ${APRG_UNIQUE_PROBLEMS_DIR}/src)

set(APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY ${APRG_UNIQUE_PROBLEMS_DIR}/tst)

set(APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY ${APRG_UNIQUE_PROBLEMS_DIR}/main)

set(APRG_UNIQUE_PROBLEMS_INCLUDE_DIRECTORIES ${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY})

set(APRG_UNIQUE_PROBLEMS_TEST_INCLUDE_DIRECTORIES ${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY}]")
get_source_files_from_directory(APRG_UNIQUE_PROBLEMS_SOURCES ${APRG_UNIQUE_PROBLEMS_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY}]")
get_source_files_from_directory(APRG_UNIQUE_PROBLEMS_TESTS ${APRG_UNIQUE_PROBLEMS_TEST_DIRECTORY})

print_status("Looking for main C/C++ files in: [${APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY}]")
get_source_files_from_directory(APRG_UNIQUE_PROBLEMS_MAIN_SOURCES ${APRG_UNIQUE_PROBLEMS_MAIN_DIRECTORY})

set(APRG_UNIQUE_PROBLEMS_SOURCES_AND_TESTS ${APRG_UNIQUE_PROBLEMS_SOURCES} ${APRG_UNIQUE_PROBLEMS_TESTS})
