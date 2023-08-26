set(GSL_TEST_TST_DIRECTORY ${GSL_TEST_DIR}/tst)

set(GSL_TEST_TST_INCLUDE_DIRECTORIES ${GSL_TEST_TST_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${GSL_TEST_TST_DIRECTORY}]")
get_source_files_from_directory(GSL_TEST_TST_FILES ${GSL_TEST_TST_DIRECTORY})
