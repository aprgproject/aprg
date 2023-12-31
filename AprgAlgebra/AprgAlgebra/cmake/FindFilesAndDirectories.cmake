set(APRG_ALGEBRA_SOURCE_DIRECTORY ${APRG_ALGEBRA_DIR}/src)

set(APRG_ALGEBRA_TEST_DIRECTORY ${APRG_ALGEBRA_DIR}/tst)

set(APRG_ALGEBRA_MAIN_DIRECTORY ${APRG_ALGEBRA_DIR}/main)

set(APRG_ALGEBRA_INCLUDE_DIRECTORIES ${APRG_ALGEBRA_SOURCE_DIRECTORY})

set(APRG_ALGEBRA_TEST_INCLUDE_DIRECTORIES ${APRG_ALGEBRA_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${APRG_ALGEBRA_SOURCE_DIRECTORY}]")
get_source_files_from_directory(APRG_ALGEBRA_SOURCES ${APRG_ALGEBRA_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${APRG_ALGEBRA_TEST_DIRECTORY}]")
get_source_files_from_directory(APRG_ALGEBRA_TESTS ${APRG_ALGEBRA_TEST_DIRECTORY})

print_status("Looking for main C/C++ files in: [${APRG_ALGEBRA_MAIN_DIRECTORY}]")
get_source_files_from_directory(APRG_ALGEBRA_MAIN_SOURCES ${APRG_ALGEBRA_MAIN_DIRECTORY})

set(APRG_ALGEBRA_SOURCES_AND_TESTS ${APRG_ALGEBRA_SOURCES} ${APRG_ALGEBRA_TESTS})
