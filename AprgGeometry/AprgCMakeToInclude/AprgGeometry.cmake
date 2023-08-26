# Assign project directory, this needs aprg directory
set(APRG_GEOMETRY_DIR ${APRG_DIR}/AprgGeometry/AprgGeometry/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GEOMETRY_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_GEOMETRY_INCLUDE_DIRECTORIES})
add_library(APRG_GEOMETRY ${APRG_GEOMETRY_SOURCES})
