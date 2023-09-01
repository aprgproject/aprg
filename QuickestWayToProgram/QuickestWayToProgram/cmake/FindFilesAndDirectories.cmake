set(QUICKEST_WAY_TO_PROGRAM_TEST_DIRECTORY ${QUICKEST_WAY_TO_PROGRAM_DIR}/tst)

set(QUICKEST_WAY_TO_PROGRAM_TEST_INCLUDE_DIRECTORIES
    ${QUICKEST_WAY_TO_PROGRAM_TEST_DIRECTORY})

print_status(
  "Looking for tests C/C++ files in: [${QUICKEST_WAY_TO_PROGRAM_TEST_DIRECTORY}]"
)
get_source_files_from_directory(QUICKEST_WAY_TO_PROGRAM_TESTS
                                ${QUICKEST_WAY_TO_PROGRAM_TEST_DIRECTORY})

set(QUICKEST_WAY_TO_PROGRAM_SOURCES_AND_TESTS ${QUICKEST_WAY_TO_PROGRAM_TESTS})
