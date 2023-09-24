# Assign project directory, this needs aprg directory
set(GNU_PLOT_WRAPPER_DIR ${APRG_DIR}/AprgGnuPlot/GnuPlotWrapper/)

set(GNU_PLOT_WRAPPER_SOURCE_DIRECTORY ${GNU_PLOT_WRAPPER_DIR}/src)

set(GNU_PLOT_WRAPPER_TEST_DIRECTORY ${GNU_PLOT_WRAPPER_DIR}/tst)

set(GNU_PLOT_WRAPPER_INCLUDE_DIRECTORIES ${GNU_PLOT_WRAPPER_SOURCE_DIRECTORY})

set(GNU_PLOT_WRAPPER_TEST_INCLUDE_DIRECTORIES
    ${GNU_PLOT_WRAPPER_TEST_DIRECTORY})

print_status(
  "Looking for sources C/C++ files in: [${GNU_PLOT_WRAPPER_SOURCE_DIRECTORY}]")
get_source_files_from_directory(GNU_PLOT_WRAPPER_SOURCES
                                ${GNU_PLOT_WRAPPER_SOURCE_DIRECTORY})

# print_status("Looking for tests C/C++ files in:
# [${GNU_PLOT_WRAPPER_TEST_DIRECTORY}]")
# get_source_files_from_directory(GNU_PLOT_WRAPPER_TESTS
# ${GNU_PLOT_WRAPPER_TEST_DIRECTORY})

include_directories(${GNU_PLOT_WRAPPER_INCLUDE_DIRECTORIES})
# add_library(GNU_PLOT_WRAPPER ${GNU_PLOT_WRAPPER_SOURCES})
