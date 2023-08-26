# Assign project directory, this needs aprg directory
set(APRG_MODELLING_DIR ${APRG_DIR}/AprgModelling/AprgModelling/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_MODELLING_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_MODELLING_INCLUDE_DIRECTORIES})
add_library(APRG_MODELLING ${APRG_MODELLING_SOURCES})
