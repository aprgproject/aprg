# Assign project directory, this needs aprg directory
set(APRG_JSON_DIR ${APRG_DIR}/AprgJson/AprgJson/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_JSON_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_JSON_INCLUDE_DIRECTORIES})
add_library(APRG_JSON ${APRG_JSON_SOURCES})
