set(FILE_DESTRUCTOR_SOURCE_DIRECTORY ${FILE_DESTRUCTOR_DIR}/src)

set(FILE_DESTRUCTOR_TEST_DIRECTORY ${FILE_DESTRUCTOR_DIR}/tst)

set(FILE_DESTRUCTOR_MAIN_DIRECTORY ${FILE_DESTRUCTOR_DIR}/main)

set(FILE_DESTRUCTOR_INCLUDE_DIRECTORIES ${FILE_DESTRUCTOR_SOURCE_DIRECTORY})

set(FILE_DESTRUCTOR_TEST_INCLUDE_DIRECTORIES ${FILE_DESTRUCTOR_TEST_DIRECTORY})

print_status("Looking for sources C/C++ files in: [${FILE_DESTRUCTOR_SOURCE_DIRECTORY}]")
get_source_files_from_directory(FILE_DESTRUCTOR_SOURCES ${FILE_DESTRUCTOR_SOURCE_DIRECTORY})

print_status("Looking for tests C/C++ files in: [${FILE_DESTRUCTOR_TEST_DIRECTORY}]")
get_source_files_from_directory(FILE_DESTRUCTOR_TESTS ${FILE_DESTRUCTOR_TEST_DIRECTORY})

print_status("Looking for main C/C++ files in: [${FILE_DESTRUCTOR_MAIN_DIRECTORY}]")
get_source_files_from_directory(FILE_DESTRUCTOR_MAIN_SOURCES ${FILE_DESTRUCTOR_MAIN_DIRECTORY})

set(FILE_DESTRUCTOR_SOURCES_AND_TESTS ${FILE_DESTRUCTOR_SOURCES} ${FILE_DESTRUCTOR_TESTS})
