set(APRG_GNU_PLOT_SOURCE_DIRECTORY ${APRG_GNU_PLOT_DIR}/src)

set(APRG_GNU_PLOT_TEST_DIRECTORY ${APRG_GNU_PLOT_DIR}/tst)

set(APRG_GNU_PLOT_INCLUDE_DIRECTORIES ${APRG_GNU_PLOT_SOURCE_DIRECTORY})

set(APRG_GNU_PLOT_TEST_INCLUDE_DIRECTORIES ${APRG_GNU_PLOT_TEST_DIRECTORY})

print_status(
  "Looking for sources C/C++ files in: [${APRG_GNU_PLOT_SOURCE_DIRECTORY}]")
get_source_files_from_directory(APRG_GNU_PLOT_SOURCES
                                ${APRG_GNU_PLOT_SOURCE_DIRECTORY})

print_status(
  "Looking for tests C/C++ files in: [${APRG_GNU_PLOT_TEST_DIRECTORY}]")
get_source_files_from_directory(APRG_GNU_PLOT_TESTS
                                ${APRG_GNU_PLOT_TEST_DIRECTORY})

set(APRG_GNU_PLOT_SOURCES_AND_TESTS ${APRG_GNU_PLOT_SOURCES}
                                    ${APRG_GNU_PLOT_TESTS})
