set(BOOST_TEST_TST_DIRECTORY ${BOOST_TEST_DIR}/tst)

set(BOOST_TEST_TST_INCLUDE_DIRECTORIES ${BOOST_TEST_TST_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${BOOST_TEST_TST_DIRECTORY}]")
get_source_files_from_directory(BOOST_TEST_TST_FILES ${BOOST_TEST_TST_DIRECTORY})
