set(JSON_LIBRARY_TEST_TST_DIRECTORY ${JSON_LIBRARY_TEST_DIR}/tst)

set(JSON_LIBRARY_TEST_TST_INCLUDE_DIRECTORIES ${JSON_LIBRARY_TEST_TST_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${JSON_LIBRARY_TEST_TST_DIRECTORY}]")
get_source_files_from_directory(JSON_LIBRARY_TEST_TST_FILES ${JSON_LIBRARY_TEST_TST_DIRECTORY})
