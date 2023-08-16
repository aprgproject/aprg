# Assign project directory, this needs aprg directory
set(APRG_GRAPH_DIR ${APRG_DIR}/AprgGraph/AprgGraph/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GRAPH_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_GRAPH_INCLUDE_DIRECTORIES})
add_library(APRG_GRAPH ${APRG_GRAPH_SOURCES})
