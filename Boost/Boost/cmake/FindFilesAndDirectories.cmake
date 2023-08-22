set(BOOST_TEST_DIRECTORY ${BOOST_DIR}/tst)

set(BOOST_TEST_INCLUDE_DIRECTORIES ${BOOST_TEST_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${BOOST_TEST_DIRECTORY}]")
get_source_files_from_directory(BOOST_TESTS ${BOOST_TEST_DIRECTORY})

include(${BOOST_DIR}/cmake/IncludeBoost.cmake)
