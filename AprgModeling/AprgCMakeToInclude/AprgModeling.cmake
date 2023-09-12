# Assign project directory, this needs aprg directory
set(APRG_MODELING_DIR ${APRG_DIR}/AprgModeling/AprgModeling/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_MODELING_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_MODELING_INCLUDE_DIRECTORIES})
add_library(APRG_MODELING ${APRG_MODELING_SOURCES})
