set(SACK_READER_SOURCE_DIRECTORY ${SACK_READER_DIR}/src)

set(SACK_READER_TEST_DIRECTORY ${SACK_READER_DIR}/tst)

set(SACK_READER_INCLUDE_DIRECTORIES ${SACK_READER_SOURCE_DIRECTORY})

set(SACK_READER_TEST_INCLUDE_DIRECTORIES ${SACK_READER_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${SACK_READER_SOURCE_DIRECTORY}]")
get_source_files_from_directory(SACK_READER_SOURCES ${SACK_READER_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${SACK_READER_TEST_DIRECTORY}]")
get_source_files_from_directory(SACK_READER_TESTS ${SACK_READER_TEST_DIRECTORY})

set(SACK_READER_SOURCES_AND_TESTS ${SACK_READER_SOURCES} ${SACK_READER_TESTS})
