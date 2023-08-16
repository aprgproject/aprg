# Assign project directory, this needs aprg directory
set(APRG_GNU_PLOT_DIR ${APRG_DIR}/AprgGnuPlot/AprgGnuPlot/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GNU_PLOT_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_GNU_PLOT_INCLUDE_DIRECTORIES})
add_library(APRG_GNU_PLOT ${APRG_GNU_PLOT_SOURCES})
